def c():
    print("c!")

def aaa():
    print("a+a+a=c")

def ba():
    print("b+a=c")

def ab():
    print("a+b=c")

def cc():
    print("!c")

def CodePass():
    # Lấy dữ liệu từ người dùng nè
    user_input = input("codepass?")
    
    if user_input == "c!!c":
        print("Wrong!")
    elif user_input == "ca^3+(b+a)(a+b)=!c":
        print("Correct!")
    else:
        print("codepass")

# Gọi hàm
c()
aaa()
ba()
ab()
cc()
CodePass()

# yes?
input("\nEnter to exit.")
# コードパス
