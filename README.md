# spam-detector
SMSSpamCollection.txt This dataset contains labelled messages. It is only for you to observe and
get an idea of what kind of information is stored in the data. It has classes and messages on each line. A line
begins with either ’spam’, indicating that the following message is a spam message, or ’ham’, indicating
that it is not a spam message. The labels are followed by a tab (\t) character that separates the classes and
messages. After the tab character, the message starts. For simplicity, you may assume that each word in the
message is seperated with a space character (” ”). At the end of each line, there is a new line (\n) character.
preprocessed dataset.txt This is the preprocessed version of the SMSSPamCollection.txt.
Mainly, words that contribute little information (called stopwords) and the punctuations are removed from
the original data.
testData.txt is a small excerpt from the preprocessed SMS Spam Collection dataset. You will use
this file to see whether your spam detector works well by comparing the output of the detector to the ground
truth values in the file.
Task 1: Count Occurrence
In this task, you will prompt the user to enter a word, and display how many times the word appeared in
spam and non-spam messages. The search should be case insensitive.
(Hint: a word may appear more than once in a message)
Sample Outputs
$ make
Please enter a word to search for: computer
The word ’computer’ appears 6 times in ham messages and 5 times in spam messages.
$ make
Please enter a word to search for: comp
The word ’computer’ appears 0 times in ham messages and 5 times in spam messages.
$ make
Please enter a word to search for: price
The word ’price’ appears 7 times in ham messages and 18 times in spam messages.
$ make
2
Please enter a word to search for: terminal
This word doesn’t occur in the text!
Task 2: Identifying Most Common Spam Words
In this task, you will identify the 10 most occurring words in the spam messages. To do this, you may need
to define a new struct to keep a count of unique words and their occurrences. Once you identify the most
common 10 words, print them in descending order.
Sample Outputs
$ make
.
.
.
Top 10 occurring words in spam messages:
call: 292 times
free: 204 times
txt: 149 times
u: 148 times
ur: 142 times
.
.
.
Task 3: Writing a Spam Detector
Your final task is to use the most common 10 words that you identified in Task 2 to label a message as spam
or ham. You should open the testData.txt file and read the lines just like in the previous parts, but this
time, implement a function that checks whether the message contains at least 3 of the words that are in the
”spam list”. If that is the case, the function should return ”spam”, otherwise it should return ”ham”.
Finally, compare the outputs of your function to the actual labels in the data and report the accuracy of
your detector.
Accuracy =
# Correct Identifications
# Total Identificaitons
(1)
(Note that the total identifications here refers to the total within their respective groups (e.g., total spam
identifications or total ham identificaitons))
Sample Outputs
$ make
.
.
.
Accuracy of spam predictions: ##.##%
Accuracy of ham predictions: ##.##%
Total spam messages: 14
