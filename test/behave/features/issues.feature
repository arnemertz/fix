Feature: creating new issues
  Scenario: create first issue
     Given an empty Fix repository
     When we create issues
        | summary      | description  |
        | First issue  | A serious problem: the issue database was empty! |
     Then an issue file "1.json" exists in the repository


