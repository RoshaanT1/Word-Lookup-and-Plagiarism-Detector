import requests
import sys
from PyDictionary import PyDictionary

def get_word_meaning(word):
    url = f"https://api.dictionaryapi.dev/api/v2/entries/en/{word}"
    response = requests.get(url)
    part = "N/A"
    mean = "N/A"
    exam = "N/A"
    synon = "N/A"
    meaning = PyDictionary()
    if response.status_code == 200:
        data = response.json()
        count=0
        for entry in data:
            if "meanings" in entry:
                meaning_found = False
                for meaning in entry["meanings"]:

                    if not meaning_found:
                        if(part=="N/A"):
                            part = meaning["partOfSpeech"]
                        # print(f"Part of Speech: {meaning["partOfSpeech"]}")


                        if "definitions" in meaning and len(meaning["definitions"]) > 0:
                            definition = meaning["definitions"][0]
                            if(mean=="N/A"):
                                mean = definition["definition"]
                            # print(f"Meaning: {definition["definition"]}")

                            # Print the first example sentence if available
                            if "example" in definition:
                                if(exam=="N/A"):
                                    exam = definition["example"]
                                # print(f"Example: {definition["example"]}")

                        if "synonyms" in meaning and meaning["synonyms"]:

                            if(synon=="N/A" and count<3):
                                synon = meaning["synonyms"][0]
                                count += 1
                            elif(count<3):
                                synon += ", " + meaning["synonyms"][0]
                                count += 1
                            # print(f"Synonym: {meaning["synonyms"][0]}")
                    if(part!="N/A" and mean!="N/A" and exam!="N/A" and synon!="N/A"):
                        with open("C:/Qt/Examples/Qt-6.8.0/widgets/tutorials/notepad/partsOfSpeech.txt", "a",encoding="utf-8", errors="replace") as partsOfSpeech:
                            partsOfSpeech.write(f"{word} {part.capitalize()}\n")
                        with open("C:/Qt/Examples/Qt-6.8.0/widgets/tutorials/notepad/meanings.txt", "a",encoding="utf-8", errors="replace") as meanings:
                            meanings.write(f"{word} {mean.capitalize()}\n")
                        with open("C:/Qt/Examples/Qt-6.8.0/widgets/tutorials/notepad/examples.txt", "a",encoding="utf-8", errors="replace") as example:
                            example.write(f"{word} {exam.capitalize()}\n")
                        with open("C:/Qt/Examples/Qt-6.8.0/widgets/tutorials/notepad/synonyms.txt", "a",encoding="utf-8", errors="replace") as synonym:
                            synonym.write(f"{word} {synon.capitalize()}\n")
                        meaning_found = True
                        break
                if(meaning_found):
                    break
        if(meaning_found==False):
            with open("C:/Qt/Examples/Qt-6.8.0/widgets/tutorials/notepad/partsOfSpeech.txt", "a",encoding="utf-8", errors="replace") as partsOfSpeech:
                if(part!='N/a'):
                    partsOfSpeech.write(f"{word} {part.capitalize()}\n")
                else:
                    partsOfSpeech.write(f"{word} {meaning.meaning(word)[0]}\n")
            with open("C:/Qt/Examples/Qt-6.8.0/widgets/tutorials/notepad/meanings.txt", "a",encoding="utf-8", errors="replace") as meanings:
                if(mean!='N/a'):
                    meanings.write(f"{word} {mean.capitalize()}\n")
                else:
                    meanings.write(f"{word} {meaning.getMeanings()}\n")
            with open("C:/Qt/Examples/Qt-6.8.0/widgets/tutorials/notepad/examples.txt", "a",encoding="utf-8", errors="replace") as example:
                example.write(f"{word} {exam.capitalize()}\n")
            with open("C:/Qt/Examples/Qt-6.8.0/widgets/tutorials/notepad/synonyms.txt", "a",encoding="utf-8", errors="replace") as synonym:
                if(synon!='N/a'):
                    synonym.write(f"{word} {synon.capitalize()}\n")
                else:
                    synonym.write(f"{word} {meaning.getSynonyms(word)}\n")
    else:
        with open("C:/Qt/Examples/Qt-6.8.0/widgets/tutorials/notepad/partsOfSpeech.txt", "a",encoding="utf-8", errors="replace") as partsOfSpeech:
            partsOfSpeech.write(f"{word} {part.capitalize()}\n")
        with open("C:/Qt/Examples/Qt-6.8.0/widgets/tutorials/notepad/meanings.txt", "a",encoding="utf-8", errors="replace") as meanings:
            meanings.write(f"{word} {mean.capitalize()}\n")
        with open("C:/Qt/Examples/Qt-6.8.0/widgets/tutorials/notepad/examples.txt", "a",encoding="utf-8", errors="replace") as example:
            example.write(f"{word} {exam.capitalize()}\n")
        with open("C:/Qt/Examples/Qt-6.8.0/widgets/tutorials/notepad/synonyms.txt", "a",encoding="utf-8", errors="replace") as synonym:
            synonym.write(f"{word} {synon.capitalize()}\n")

old_words = set()
def getOldWord():
    with open('C:/Qt/Examples/Qt-6.8.0/widgets/tutorials/notepad/synonyms.txt', 'r',encoding="utf-8", errors="replace") as file:
        for line in file:
            first_word = line.split()[0] if line.strip() else None
            if first_word!=None:
                old_words.add(first_word)

def process_sentence(sentence):
    getOldWord()
    words = sentence.split()
    ignore = ['and','is','in','the','that','you','us','me','we','they']
    for word in words:
        updated_word = word.replace(",", "").replace(".", "").lower()
        if updated_word not in old_words:
            get_word_meaning(updated_word)
            old_words.add(updated_word)


if __name__ == "__main__":
    if len(sys.argv) > 1:
        sentence = " ".join(sys.argv[1:])
        process_sentence(sentence)
