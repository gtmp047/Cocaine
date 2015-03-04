import msgpack

json={"a":"value","b":42}

pack=msgpack.packb(json)

f = open('out.txt').read()

unpack=msgpack.unpackb(f)

print unpack