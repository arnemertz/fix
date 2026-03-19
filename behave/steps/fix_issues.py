from behave import given, when, then, use_step_matcher
import re
import fix_cli


@given(u'an empty issue repository')
def empty_repository(context):
    pass  # handled by environment.py before_scenario


@when(u'we list all issues')
def list_issues(context):
    fix_cli._start_fix_with_args(context, ['list'])


def _create_issue(context, title, description):
    fix_cli._start_fix_with_args(context, ['create', '--title', title, '--descr', description])


# Use regex matcher to capture any title including empty string
use_step_matcher("re")


@when(u'we create an issue titled "(?P<title>[^"]*)" with description')
def create_issue(context, title):
    description = context.text or ""
    _create_issue(context, title, description)


@when(u'we create an issue titled "(?P<title>[^"]*)"')
def create_issue_random_description(context, title):
    description = "Dorem Fixum dolor sit amet..."
    _create_issue(context, title, description)


use_step_matcher("parse")


@then(u'it prints a list of issues')
def check_issue_list(context):
    for row in context.table:
        id_prefix = row["issue ID prefix"]
        title = row["title"]
        status = row["status"]
        fix_cli.check_output_regex(context, rf'{id_prefix}-[0-9a-f]{{7}} \| {title} \| {status}')


@then(u'it prints a list of {count:d} issues')
def check_issue_list_count(context, count):
    check_issue_list(context)
    fix_cli.check_output(context, f"total: {count} issues")
