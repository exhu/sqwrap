
class MyB extends MyClsA{
    a = 0

    constructor() {
        base.constructor()
    }

    function dosmth() {
        a = 3
    }

}


print("hello, world!\n")
print(typeof(MyClsA)+"\n");
local a = MyClsA()
local b = MyB()
print(b)
foreach(k,v in b.getclass()) print(k+" = "+v+"\n")


print(a.GetNumber()+"\n")
a.SetNumber(333)
print(a.GetNumber()+"\n")
a.SetNumber(34.3)
print(a.GetNumber()+"\n")
