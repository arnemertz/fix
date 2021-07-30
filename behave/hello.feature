Feature: starting Fix (behave initial setup)

  Scenario: run the simple Hello World app that Fix is today
    Given nothing
    When we run Fix
    Then it prints "Hello, fix!" and terminates
