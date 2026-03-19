import os
import shutil
import tempfile


def before_scenario(context, scenario):
    # Each scenario gets a fresh temp directory with a .fix/issues structure
    context.temp_dir = tempfile.mkdtemp(prefix="fix_test_")
    context.fix_dir = os.path.join(context.temp_dir, ".fix", "issues")
    os.makedirs(context.fix_dir)
    context.original_dir = os.getcwd()
    os.chdir(context.temp_dir)


def after_scenario(context, scenario):
    os.chdir(context.original_dir)
    shutil.rmtree(context.temp_dir, ignore_errors=True)
