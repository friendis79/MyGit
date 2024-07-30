#시저 암호 프로그램 구현
key = "abcdefghijklmnopqrstuvwxyz"

#평문을 받아서 암호화하고 암호문을 반환한다.
def encrypt(n, plaintext):
    result = ""
    
    for I in plaintext.lower(): #lower -> 소문자로 바꿈
        try :
            i = (key.index(I) + n) % 26
            result += key[i]
            
        except ValueError:
                result += I
    return result.lower()
    
#암호문을 받아서 복호화하고 평문을 반환한다.
def decrypt(n, ciphertext):
    result = ''
    for I in ciphertext:
        try :
            i = (key.index(I) - n) % 26
            result += key[i]
        except ValueError:
            result += I
    return result

n = 3
text = "The language of truth is simple."
encryped = encrypt(n, text)
decryped = decrypt(n, encryped)
print("평 문 : ", text)
print("암호문 : ", encryped)
print("복호문 : ", decryped)