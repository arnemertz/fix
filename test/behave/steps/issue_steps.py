import json
import requests
from behave import *


@given('an empty Fix repository')
def step_impl(context):
    del context


@given('a Fix repository with issues')
def step_impl(context):
    table = context.table
    issue_keys = table.headings
    for row in table:
        create_issue_file(context, issue_keys, row)


def create_issue_file(context, issue_keys, row):
    issue_json = extract_issue_json(issue_keys, row)
    issue_id = issue_json['data']['ID']
    issue_filename = issue_id + '.json'
    file_content = json.dumps(issue_json, sort_keys=True, indent=4, separators=(',', ': '))
    fix_context = context.fix_context
    fix_context.create_issue_file(issue_filename, file_content)


@when('we create issues')
def step_impl(context):
    table = context.table
    issue_keys = table.headings
    for row in table:
        issue_json = extract_issue_json(issue_keys, row)
        create_issue_rest(issue_json)


@then('an issue file "{file_name}" exists in the repository')
def step_impl(context, file_name):
    assert context.fix_context.issue_file_exists(file_name)


@then('an issue file "{file_name}" does not exist in the repository')
def step_impl(context, file_name):
    assert not context.fix_context.issue_file_exists(file_name)


def create_issue_rest(issue_json):
    r = requests.post('http://localhost:8080/issue/new', json=issue_json)
    assert r.status_code == 200


def extract_issue_json(issue_keys, row):
    issue_data = {}
    for key in issue_keys:
        issue_data[key] = row[key]
    issue_json = {'data': issue_data}
    return issue_json
