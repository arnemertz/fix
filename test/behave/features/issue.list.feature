#Feature: listing all issues
#
#  Scenario: Empty list
#    Given an empty Fix repository
#    When we list all issues
#    Then the response is a list with 0 entries
#
#  Scenario: List with mutiple items
#    Given a Fix repository with issues
#      | ID | summary       | description        |
#      | 1  | First issue   | Issue number one.  |
#      | 2  | Number two    | Issue number two.  |
#      | 3  | The third     | Some description.  |
#      | 7  | A Later issue | There will be more |
#    When we list all issues
#    Then the response is a list with 4 entries
#      | ID | summary       |
#      | 1  | First issue   |
#      | 2  | Number two    |
#      | 3  | The third     |
#      | 7  | A Later issue |
