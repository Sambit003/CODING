character = input("\n\tEnter a character: ")
if character in ['a','e','i','o','u','A','E','I','O','U']:
    print("\n\tThe character is a vowel.")
elif (character >= 'a' and character <= 'z') or (character >= 'A' and character <= 'Z'):
    print("\n\tThe character is a consonent.")
else:
    print("\n\tThe character is not an alphabet.")