from tempfile import mkdtemp
import shutil
import subprocess

def before_scenario(context, scenario):
    context.tempdir = mkdtemp()
    context.fixprocess = subprocess.Popen(['fix'], cwd=context.tempdir)

def after_scenario(context, scenario):
    context.fixprocess.kill()
    if not context.failed:
        shutil.rmtree(context.tempdir)

