from pathlib import Path
import requests
import subprocess
import time


class FixContext:
    def __init__(self, base_dir):
        self.__base_dir = base_dir
        self.__process = subprocess.Popen(['fix'], cwd=base_dir)
        FixContext.wait_for_server_startup()

    @staticmethod
    def wait_for_server_startup():
        startup = time.clock()
        while time.clock() < startup + 10:
            try:
                requests.get('http://localhost:8080/')
                return
            except requests.ConnectionError:
                pass
        assert "" != "Connection to server timed out!"

    def finish(self):
        self.__process.kill()

    def get_base_dir(self):
        return self.__base_dir

    def get_issue_dir(self):
        issue_dir = self.__get_fix_dir() + 'issues/'
        return issue_dir

    def __get_fix_dir(self):
        fix_dir = self.get_base_dir() + '/.fix/'
        return fix_dir

    def issue_file_exists(self, file_name):
        issue_dir = self.get_issue_dir()
        expected_file = Path(issue_dir + file_name)
        return expected_file.exists()

    def create_issue_file(self, filename, content):
        issue_dir = self.get_issue_dir()
        issue_file = Path(issue_dir + filename)
        assert not issue_file.exists()
        with open(str(issue_file), 'w') as f:
            f.write(content)
