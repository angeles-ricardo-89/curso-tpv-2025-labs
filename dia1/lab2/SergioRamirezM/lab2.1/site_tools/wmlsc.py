from SCons.Script import *


def generate(env):
    wmlsc_builder = Builder(action='wmlsc -on $SOURCE $TARGET',
                            suffix='.wmlsc',
                            src_suffix=".wmls",
                            single_source=True)
    env.Append(BUILDERS={'WMLSC': wmlsc_builder})


def exists(env):
    return True
