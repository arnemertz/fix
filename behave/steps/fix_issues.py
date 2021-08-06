from behave import given, when, then
import fix_cli

@given(u'an empty issue repository')
def empty_repository(context):
    pass

@when(u'we list all issues')
def list_issues(context):
    fix_cli.start_fix(context, "list")
