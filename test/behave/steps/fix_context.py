class FixContext:
    def __init__(self, tempdir):
        self._tempdir = tempdir
        pass

    def get_tempdir(self):
        return self._tempdir
