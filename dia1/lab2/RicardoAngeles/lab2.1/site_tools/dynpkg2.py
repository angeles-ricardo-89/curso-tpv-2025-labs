from SCons.Script import *
import zipfile
import re
import os


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


def process_appfile(target, source, env):
    app_file_name = 'app.' + env['PROJECT_NAME']
    base_dir = env['PROJECT_BASE_DIR']
    # app_def = load_appfile(os.path.join(base_dir, 'src', app_file_name))
    actions = []

    actions.append(gen_create_appzip(source, target, env))
    new_distdir = os.path.dirname(str(target[0]))
    napp_file = env.Command(os.path.join(new_distdir, app_file_name),
                            os.path.join(base_dir, 'src', app_file_name),
                            Copy('$TARGET', '$SOURCE'))

    # mk_folders(app_def, env, new_distdir)
    app_objs, conf_objs, res_objs = distribute_objects(source, env)

    add_app_objs = env.Command(target, app_objs,
                               "tpvasset add --app $TARGET $SOURCE")
    add_conf_objs = env.Command(target, conf_objs,
                                "tpvasset add --config $TARGET $SOURCE")
    add_res_objs = env.Command(target, res_objs,
                               "tpvasset add --res $TARGET $SOURCE")

    actions.append(add_app_objs)
    actions.append(add_conf_objs)
    actions.append(add_res_objs)
    return target[0], actions


def gen_create_appzip(source, target, env):
    app_file_name = 'app.' + env['PROJECT_NAME']
    base_dir = env['PROJECT_BASE_DIR']
    src_filename = os.path.join(base_dir, 'src', app_file_name)
    # return env.Command(target, src_filename, 'tpvmk --clone $SOURCE $TARGET')
    return f'tpvmk --clone {src_filename} {str(target)}'


def gen_assets_builder(source, target, env, mode):
    source = ' '.join([str(s) for s in source])
    return f'tpvasset add --{mode} {str(target)} {source}'


def zippkg2(target, source, env, for_signature):
    app_file_name = 'app.' + env['PROJECT_NAME']
    base_dir = env['PROJECT_BASE_DIR']
    app_file = gen_create_appzip(source, target[0], env)
    app_objs, conf_objs, res_objs = distribute_objects(source, env)
    add_app_objs = gen_assets_builder(app_objs, target[0], env, 'app')
    add_conf_objs = gen_assets_builder(conf_objs, target[0], env, 'config')
    add_res_objs = gen_assets_builder(res_objs, target[0], env, 'res')
    return '\n'.join([app_file, add_app_objs, add_conf_objs, add_res_objs])


def generate(env):
    pkg_builder = Builder(generator=zippkg2)
    env.Append(BUILDERS={'ZIPPKG2': pkg_builder})


def exists(env):
    return True

