from SCons.Script import *
from os.path import join as pjoin
from os.path import exists as pexists
from os.path import basename as pbasename
from pathlib import Path
from platform import system
from tpvutils import PACKAGING_VALUES
from typing import List


class Project(object):
    wmls_dirs: []
    wml_dirs: []
    conf_dirs: []
    res_dirs: []
    m4includes: []

    def __init__(self, base_dir, project_name):
        self.environment = configure_environment(base_dir, project_name)
        self.build_mode = self.environment['BUILD_TYPE']
        self.packaging = self.environment['PACKAGING']
        self.base_dir = base_dir
        self.project_name = project_name
        self.__set_base_project_paths(base_dir)

    def __set_base_project_paths(self, base_dir):
        self.m4includes = [pjoin(base_dir, 'm4includes'), ]

        self.bin_dir = f'build/{self.build_mode}/bin'
        self.dist_dir = f'build/{self.build_mode}/dist/{self.packaging}'
        self.intermediate_dir = f'build/{self.build_mode}/intermediate'

        self.src_wmls_dir = pjoin(base_dir, 'src', 'wmls')
        self.src_pwmls_dir = pjoin(self.src_wmls_dir, self.packaging)

        self.src_wml_dir = pjoin(base_dir, 'src', 'wml')
        self.src_pwml_dir = pjoin(self.src_wml_dir, self.packaging)

        self.src_conf_dir = pjoin(base_dir, 'src', 'conf')
        self.src_pconf_dir = pjoin(self.src_conf_dir, self.packaging)

        self.src_res_dir = pjoin(base_dir, 'assets')
        self.src_pres_dir = pjoin(self.src_res_dir, self.packaging)

        self.environment['DIST_DIR'] = self.dist_dir

        self.wmls_dirs = [self.src_wmls_dir, self.src_pwmls_dir]
        self.wml_dirs = [self.src_wml_dir, self.src_pwml_dir]
        self.conf_dirs = [self.src_conf_dir, self.src_pconf_dir]
        self.res_dirs = [self.src_res_dir, self.src_pres_dir]

    def __configure_m4(self):
        m4flags = ' '.join([f'-I{m4Inc}' for m4Inc in self.m4includes])
        if self.build_mode == 'debug':
            m4flags = f'-D DEBUG=1 {m4flags}'
        self.environment.Append(M4FLAGS=m4flags)
        self.environment.VariantDir(self.intermediate_dir, 'src', duplicate=0)
        self.environment.VariantDir(self.bin_dir, self.intermediate_dir,
                                    duplicate=0)
        self.environment.VariantDir(self.dist_dir, self.bin_dir, duplicate=0)

    def add_wmls_path(self, path):
        path = pjoin(self.src_wmls_dir, path)
        self.wmls_dirs.append(path)

    def add_wml_path(self, path):
        path = pjoin(self.src_wml_dir, path)
        self.wml_dirs.append(path)

    def add_conf_path(self, path):
        path = pjoin(self.src_conf_dir, path)
        self.conf_dirs.append(path)

    def add_res_path(self, path):
        path = pjoin(self.src_res_dir, path)
        self.res_dirs.append(path)

    def add_m4_path(self, path):
        path = pjoin(pjoin(self.base_dir, 'm4includes'), path)
        self.m4includes.append(path)

    def __get_m4_files(self):
        # return Glob(self.m4includes + '/*.m4')
        return self.__get_files(self.m4includes, '{}/*.m4')

    def __get_files(self, list_dirs, fmt):
        filelist = []
        for d in list_dirs:
            dir_scan = fmt.format(d)
            print(f'scanning {dir_scan}')
            if pexists(d):
                filelist = filelist + Glob(dir_scan)
        return filelist

    def __get_wmls_files(self):
        return self.__get_files(self.wmls_dirs, '{}/*.wmls')

    def __get_wml_files(self):
        return self.__get_files(self.wml_dirs, '{}/*.wml')

    def __get_conf_files(self):
        return self.__get_files(self.conf_dirs, '{}/*.*')

    def __get_res_files(self):
        return self.__get_files(self.res_dirs, '{}/*.*')

    def __do_m4(self, env, target_dir, wmls):
        menv = env.Clone()
        menv.Append(M4FLAGS=[f"-D__FILENAME__={wmls}"])
        return menv.M4(target=pjoin(target_dir,
                                    pbasename(str(wmls))),
                       source=wmls)

    def __preprocess(self, files, target):
        target_dir = pjoin(self.intermediate_dir, target)
        return [self.__do_m4(self.environment, target_dir, f)
                for f in files]

    def __preprocess_wmls(self, files):
        return self.__preprocess(files, 'wmls')

    def __preprocess_wml(self, files):
        return self.__preprocess(files, 'wml')

    def __preprocess_conf(self, files):
        return self.__preprocess(files, 'conf')

    def build(self):
        self.__configure_m4()
        m4files = self.__get_m4_files()
        wmls_filelist = self.__get_wmls_files()
        wml_filelist = self.__get_wml_files()
        conf_filelist = self.__get_conf_files()
        res_filelist = self.__get_res_files()

        wmls_procs = self.__preprocess_wmls(wmls_filelist)
        wml_procs = self.__preprocess_wml(wml_filelist)
        conf_procs = self.__preprocess_conf(conf_filelist)

        wmls_objects \
            = [self.environment.WMLSC(pjoin(self.bin_dir,
                                            Path(str(a)).stem), a)
               for a in wmls_procs]

        Depends(wmls_procs, m4files)
        Depends(wml_procs, m4files)
        Depends(conf_procs, m4files)

        if self.packaging in ["engage", "android"]:
            app = self.environment.ZIPPKG2(pjoin(self.dist_dir,
                                                 f'{self.project_name}.zip'),
                                           wmls_objects
                                           + wml_procs
                                           + conf_procs
                                           + res_filelist)
            Depends(app, wmls_objects)
            Depends(app, wml_procs)
            Depends(app, conf_procs)
            Depends(app, res_filelist)
        elif packaging == "verix":
            print("make ddl")


def configure_path(base_dir):
    os.environ["PATH"] = os.pathsep.join([pjoin(base_dir, 'tools'),
                                          os.environ["PATH"]])
    m4dir = None
    if system() == 'Windows':
        os.environ["PATH"] = os.pathsep.join([pjoin(base_dir, 'tools',
                                                    'M4', 'bin'),
                                              os.environ["PATH"]])
        m4dir = os.path.join(base_dir,  'tools\\M4\\bin\\m4.exe')
    return m4dir


def setup_default_vars():
    c_vars = Variables(None, ARGUMENTS)
    c_vars.Add(EnumVariable('BUILD_TYPE', 'type of build to use', 'release',
                            allowed_values=('debug', 'release')))
    c_vars.Add(EnumVariable('PACKAGING', 'type package destination', 'engage',
                            allowed_values=(PACKAGING_VALUES)))
    return c_vars


def configure_environment(base_dir, project_name):
    c_vars = setup_default_vars()

    env_options = {"variables": c_vars,
                   "toolpath": ["site_tools"],
                   "tools": ["zipbetter", "wmlsc", "mingw", "dyn_pkg",
                             "dynpkg2"],
                   "PROJECT_NAME": project_name,
                   "PROJECT_BASE_DIR": base_dir}

    m4dir = configure_path(base_dir)
    if m4dir:
        env_options['M4'] = m4dir

    common_env = Environment(**env_options)
    common_env['ENV']['PATH'] = os.environ['PATH']

    return common_env


def get_basic_configuration(base_dir, project_name):
    return Project(base_dir, project_name)
