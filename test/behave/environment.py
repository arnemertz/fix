from tempfile import mkdtemp
import shutil
import subprocess
from steps.fix_context import FixContext


def before_scenario(context, scenario):
    del scenario
    tempdir = mkdtemp()
    context.fix_context = FixContext(tempdir)
    context.fix_process = subprocess.Popen(['fix'], cwd=tempdir)


def after_scenario(context, scenario):
    del scenario
    context.fix_process.kill()
    if not context.failed:
        shutil.rmtree(context.fix_context.get_tempdir())

