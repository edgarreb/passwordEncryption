// Name: Edgar Martinez

Background: 

The idea for this project began when I was no longer able to keep track of my passwords for all of my online accounts/subscriptions. I wanted to create a program that would take a file with all of my personal login information and encrypt it. The idea was that I would have a copy of this encrypted file on my computer that I could decrypt whenever I needed to. I didn't just want to have a file on my computer with all of my login info for somebody to snoop at so easily, so I decided to make it harder for them ! Along the way I learned how some common encryption scemes work, and ways to implement them. 



Implementation: 

I implemented what is called a Ceaser Cipher encryption scheme in my initial program. The Ceaser Cipher is one of the most basic encryption schemes used today. The way it works is by replacing a single character by some offset value. In this implementation I would swap characters with their corresponding offset counterpart from the ascii table. The downsides to this type of encryption style is that it can be easily broken by trying simply trying all possible offsets until the message us decrypted. 

In my second implementation I used an approach that I thought of myself. In this scheme I would generate random offset values for each character, and hide them within sets of additonal random characters. 

	example: 

	"A" could be encrypted into "@" 
	then placed in a random string of characters "jH@45_k~)wEz"\" at position 2

This approach would require the program to remember the offset for each character, the amount of additional characters added, and where the "payload" charcater was hidden within the random string of additonal characters. It also made decrypting my message alot more difficult. Each time the file was encrypted it would result in a different encryption because of the randomness of the program (used rand() function, and time from the Operating System at run time to achieve this).



Additional Features:

I would like to implement more ecnryption schemes, and a way to encrypt multiple files and store them at some given location (other than the current directory).



Running Program:

	compile: g++ main.cpp encryption.cpp decryption.cpp
	then run...
