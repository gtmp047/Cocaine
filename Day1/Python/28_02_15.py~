import msgpack

from cocaine import services

s = services.Service('group_1')

ar = s.enqueue('foo', msgpack.packb(''))

r = ar.get()

print r
