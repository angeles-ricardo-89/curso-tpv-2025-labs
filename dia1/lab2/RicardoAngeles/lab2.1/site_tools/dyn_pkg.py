from SCons.Script import *
import zipfile
import re


def zipbetter2(target, source, env):
    # Open the zip file with appending, so multiple calls will add more files
    dist_dir = env['DIST_DIR']
    zf = zipfile.ZipFile(str(target[0]), 'a', zipfile.ZIP_DEFLATED)
    for s in source:
        # Find the path of the base file
        basedir = os.path.dirname(str(s))
        if s.isdir():
            # If the source is a directory, walk through its files
            for dirpath, dirnames, filenames in os.walk(str(s)):
                for fname in filenames:
                    path = os.path.join(dirpath, fname)
                    if os.path.isfile(path):
                        # If this is a file, write it with its relative path
                        zf.write(path, os.path.relpath(path, basedir))
        else:
            # Otherwise, just write it to the file
            flatname = os.path.basename(str(s))
            zf.write(str(s), os.path.relpath(str(s), dist_dir))
    zf.close()


def load_appfile(appfile):
    appfile_dict = {}
    with open(appfile, 'r') as f:
        for line in f.readlines():
            m = re.match(r'^([\w_]+)=(.*)$', line)
            if m is None:
                continue
            appfile_dict[m.group(1)] = m.group(2)
    return appfile_dict


def get_folders(app_def):
    app_install_folder = app_def.get('app_install_folder', None)
    app_resources_folder = app_def.get('app_resources_folder', None)
    app_config_folder = app_def.get('app_config_folder', None)
    return app_install_folder, app_config_folder, app_resources_folder


def mk_folders(app_def, env, new_dist_dir):
    actions = []
    app_install_folder, app_config_folder, app_resources_folder = \
        get_folders(app_def)

    if app_install_folder:
        actions.append(Mkdir(os.path.join(new_dist_dir, app_install_folder)))

    if app_resources_folder:
        actions.append(Mkdir(os.path.join(new_dist_dir, app_resources_folder)))

    if app_config_folder:
        actions.append(Mkdir(os.path.join(new_dist_dir, app_config_folder)))
    Execute(actions)


def is_conf_obj(tobj):
    return 'conf' in str(tobj)


def is_res_obj(tobj):
    return 'assets' in str(tobj)


def is_app_obj(tobj):
    return ('bin' in str(tobj)) or ('wmls' in str(tobj)) \
        or ('.wml' in str(tobj))


def distribute_objects(source, env):
    app_objs = []
    conf_objs = []
    res_objs = []

    for obj in source:
        if is_app_obj(obj):
            app_objs.append(obj)
        elif is_conf_obj(obj):
            conf_objs.append(obj)
        elif is_res_obj(obj):
            res_objs.append(obj)
    return app_objs, conf_objs, res_objs


def zip_objects(source, env, actions, new_dist_dir, app_objs, conf_objs,
                res_objs, app_def):
    app_install_folder, app_config_folder, app_resources_folder = \
        get_folders(app_def)

    if app_install_folder:
        appzip_folder = os.path.join(new_dist_dir,
                                     app_install_folder,
                                     app_install_folder + '.zip')
        app_zip = env.ZipBetter(appzip_folder, app_objs)
        actions.append(app_zip)

    if app_config_folder != '':
        appconf_folder = os.path.join(new_dist_dir, app_config_folder,
                                      app_config_folder + '.zip')
        conf_zip = env.ZipBetter(appconf_folder, conf_objs)
        actions.append(conf_zip)

    if app_resources_folder != '':
        appres_folder = os.path.join(new_dist_dir, app_resources_folder,
                                     app_resources_folder + '.zip')
        res_zip = env.ZipBetter(appres_folder, res_objs)
        actions.append(res_zip)


def process_appfile(target, source, env):
    app_file_name = 'app.' + env['PROJECT_NAME']
    base_dir = env['PROJECT_BASE_DIR']
    app_def = load_appfile(os.path.join(base_dir, 'src', app_file_name))
    actions = []
    new_distdir = os.path.dirname(str(target[0]))
    napp_file = env.Command(os.path.join(new_distdir, app_file_name),
                            os.path.join(base_dir, 'src', app_file_name),
                            Copy('$TARGET', '$SOURCE'))

    mk_folders(app_def, env, new_distdir)
    app_objs, conf_objs, res_objs = distribute_objects(source, env)
    zip_objects(source, env, actions, new_distdir, app_objs, conf_objs,
                res_objs, app_def)
    actions.append(napp_file)

    return target[0], actions


def generate(env):
    pkg_builder = Builder(action=zipbetter2,
                          emitter=process_appfile)
    env.Append(BUILDERS={'ZIPPKG': pkg_builder})


def exists(env):
    return True
