from tempfile import mkdtemp
import shutil
from steps.fix_context import FixContext


def before_all(context):
    import logging
    logging.getLogger("requests").setLevel(logging.WARNING)
    del context


def before_scenario(context, scenario):
    del scenario
    fix_base_dir = mkdtemp()
    context.fix_context = FixContext(fix_base_dir)


def after_scenario(context, scenario):
    del scenario
    context.fix_context.finish()
    if not context.failed:
        shutil.rmtree(context.fix_context.get_base_dir())

