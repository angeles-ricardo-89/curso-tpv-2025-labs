import zipfile
import os
from SCons.Script import *


def zipbetter(target, source, env):
    # Open the zip file with appending, so multiple calls will add more files
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
            zf.write(str(s), flatname)
    zf.close()


# Make a builder using the zipbetter function, that takes SCons files
def generate(env):
    zipbetter_bld = Builder(action=zipbetter,
                            target_factory=SCons.Node.FS.default_fs.Entry,
                            source_factory=SCons.Node.FS.default_fs.Entry)
    env.Append(BUILDERS={'ZipBetter': zipbetter_bld})


def exists(env):
    return True

