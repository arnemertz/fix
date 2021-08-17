from behave import given, when, then
from assertions import *
import pexpect
import shlex

fix_executable = '../cmake-build-debug/bin/fix'


def _start_fix_with_args(context, args):
    context.fix = pexpect.spawn(fix_executable, args=args)


@when(u'we call Fix with argument list "{args}"')
def start_fix(context, args):
    _start_fix_with_args(context, shlex.split(args.strip(), posix=True))


@when(u'we call Fix without arguments')
def start_fix_no_args(context):
    _start_fix_with_args(context, [])


@then(u'it prints "{output}"')
def check_output(context, output):
    pattern = output.replace("[hash]", "[0-9a-f]{7}")
    if pattern != output: context.fix.expect(pattern)
    else: context.fix.expect_exact(output)


@then(u'it prints usage information')
def check_usage(context):
    usage = "usage: fix [--help] <command> [<args>...]"
    check_output(context, usage)


@then(u'it prints a list of available commands')
def check_commands(context):
    command_list = """Available commands:
   create        Create a new issue
   setstatus     Set the status of an issue
   list          List all existing issues
   show          Show a specific issue
""".replace("\n", "\r\n")
    check_output(context, command_list)


@then(u'terminates with exit code {ec:l}')
def check_exit_code_alpha(context, ec):
    map = {"OK": 0, "ERROR": 1}
    assert_equals(context.fix.wait(), map[ec])
