from behave import given, when, then
import pexpect

fix_executable = '../cmake-build-debug/bin/fix'


@given(u'nothing')
def nothing(context):
    pass


def _start_fix_with_args(context, args):
    context.fix = pexpect.spawn(fix_executable, args=args)


@when(u'we call Fix with argument list "{args}"')
def start_fix(context, args):
    _start_fix_with_args(context, args.strip().split(" "))


@when(u'we call Fix without arguments')
def start_fix(context):
    _start_fix_with_args(context, [])


@then(u'it prints "{output}"')
def check_output(context, output):
    context.fix.expect_exact(output)


@then(u'it prints usage information')
def check_usage(context):
    usage = "usage: fix [--help] <command> [<args>]"
    check_output(usage)


@then(u'it prints a list of available commands')
def check_commands(context):
    command_list = """Available commands:
   create        Create a new issue
   setstatus     Set the status of an issue
   list          List all existing issues
   show          Show a specific issue
"""
    check_output(command_list)


@then(u'terminates with exit code {ec:d}')
def check_output(context, ec):
    assert (context.fix.wait() == ec)
