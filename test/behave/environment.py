from tempfile import mkdtemp
import shutil
import subprocess
import requests


def before_scenario(context, scenario):
    del scenario
    context.tempdir = mkdtemp()
    context.fix_process = subprocess.Popen(['fix'], cwd=context.tempdir)


def after_scenario(context, scenario):
    del scenario
    context.fix_process.kill()
    if not context.failed:
        shutil.rmtree(context.tempdir)

