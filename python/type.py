from __future__ import annotations
import typing


class Test:
    def __init__(self, ival: int, sval: str, children: typing.List[Test]):
        self.ival = ival
        self.sval = sval
        self.children = children

    def show(self):
        print(self.ival)
        print(self.sval)
        print("children")
        for c in self.children:
            c.show()


test = Test(ival=1, sval="hoge", children=[])
test2 = Test(ival=2, sval="fuga", children=[test])
test2.show()
