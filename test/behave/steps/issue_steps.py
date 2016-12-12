import json
import requests
from behave import *


@given('an empty Fix repository')
def step_impl(context):
    del context


@given('a Fix repository')
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
        create_issue_rest(context, issue_json)


@when('we create an issue')
def step_impl(context):
    table = context.table
    issue_keys = table.headings
    issue_values = table.rows
    assert (len(issue_values) is 1)
    issue_json = extract_issue_json(issue_keys, issue_values[0])
    create_issue_rest(context, issue_json)


@when('we list all issues')
def step_impl(context):
    context.rest_response = requests.get('http://localhost:8080/issue/list')


@when('we query the issue with ID {issue_id:d}')
def step_impl(context, issue_id):
    context.rest_response = requests.get('http://localhost:8080/issue/' + str(issue_id))


@then('an issue file "{file_name}" exists in the repository')
def step_impl(context, file_name):
    assert context.fix_context.issue_file_exists(file_name)


@then('an issue file "{file_name}" does not exist in the repository')
def step_impl(context, file_name):
    assert not context.fix_context.issue_file_exists(file_name)


@then('the response is a list with {count:d} entries')
def step_impl(context, count):
    response_data = get_response_data(context)
    response_list = response_data["issues"]
    assert (isinstance(response_list, list))
    assert count == len(response_list)
    issue_list = table_to_json_list(context)
    for issue_json in issue_list:
        assert issue_json in response_list


@then('the response is an object')
def step_impl(context):
    response_data = get_response_data(context)
    assert response_data
    expected_object = table_to_json_list(context)[0]
    assert response_data == expected_object


def table_to_json_list(context):
    table = context.table
    table_objects = []
    if table:
        keys = table.headings
        for row in table:
            table_objects.append(row_to_object(keys, row))
    return table_objects


def get_response_data(context):
    assert_response_code(context, 200)
    response_json = context.rest_response.json()
    response_data = response_json["data"]
    return response_data


def create_issue_rest(context, issue_json):
    context.rest_response = requests.post('http://localhost:8080/issue/new', json=issue_json)


def extract_issue_json(issue_keys, row):
    return {'data': (row_to_object(issue_keys, row))}


def row_to_object(keys, row):
    issue_data = {}
    for key in keys:
        issue_data[key] = row[key]
    return issue_data


@then('the response has http code {code:d}')
def step_impl(context, code):
    assert_response_code(context, code)


def assert_response_code(context, code):
    assert context.rest_response.status_code == code
