from typing import Dict


d: Dict[str, str] = {}
key_value_tuple1 = ('key1', 'value1')
key_value_tuple2 = ('key2', 'value2')
d.update([key_value_tuple1])
d.update([key_value_tuple2])
print(d)
