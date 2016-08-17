from behave import *
from pathlib import Path
import requests
import json


@given('an empty Fix repository')
def step_impl(context):
    del context


@given('a Fix repository with issues')
def step_impl(context):
    table = context.table
    issue_keys = table.headings
    issue_dir = get_issue_dir(context)
    for row in table:
        issue_json = extract_issue_json(issue_keys, row)
        create_issue_file(issue_json, issue_dir)


@when('we create issues')
def step_impl(context):
    table = context.table
    issue_keys = table.headings
    for row in table:
        issue_json = extract_issue_json(issue_keys, row)
        create_issue_rest(issue_json)


@then('an issue file "{file_name}" exists in the repository')
def step_impl(context, file_name):
    assert file_exists(file_name, context)


@then('an issue file "{file_name}" does not exist in the repository')
def step_impl(context, file_name):
    assert not file_exists(file_name, context)


def file_exists(file_name, context):
    issue_dir = get_issue_dir(context)
    expected_file = Path(issue_dir + file_name)
    return expected_file.exists()


def get_fix_dir(context):
    fix_dir = context.tempdir + '/.fix/'
    create_if_missing_dir(fix_dir)
    return fix_dir


def get_issue_dir(context):
    issue_dir = get_fix_dir(context) + 'issues/'
    create_if_missing_dir(issue_dir)
    return issue_dir


def create_if_missing_dir(issue_dir):
    issue_path = Path(issue_dir)
    if not issue_path.exists():
        issue_path.mkdir()


def extract_issue_json(issue_keys, row):
    issue_data = {}
    for key in issue_keys:
        issue_data[key] = row[key]
    issue_json = {'data': issue_data}
    return issue_json


def create_issue_rest(issue_json):
    r = requests.post('http://localhost:8080/issue/new', json=issue_json)
    assert r.status_code == 200


def create_issue_file(issue_json, issue_dir):
    issue_id = issue_json['data']['ID']
    issue_filename = issue_id + '.json'
    issue_file = Path(issue_dir + issue_filename)
    assert not issue_file.exists()
    with open(str(issue_file), 'w') as f:
        f.write(json.dumps(issue_json, sort_keys=True, indent=4, separators=(',', ': ')))
