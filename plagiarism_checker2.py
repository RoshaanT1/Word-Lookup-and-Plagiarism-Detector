import requests
import sys


def plagarismDetect(text):
    url = "https://api.gowinston.ai/v2/plagiarism"
    payload = {
        "text": text
        }
    headers = {
        "Authorization": "Bearer YdhU4aG2uFzkjeCDsaRwiXNkkdCEtkZP60I8zHokc8194002",
        "Content-Type": "application/json"
    }

    response = requests.request("POST", url, json=payload, headers=headers)

    data = response.json()
# print(data)
    score = data['result']['score']
    words = data['result']['textWordCounts']
# Extract the indexes
    indexes = data['indexes']

# Print the results
    with open("C:/Qt/Examples/Qt-6.8.0/widgets/tutorials/notepad/plagiarism_output.txt", "w") as file:
        file.write(f"{words}\n")
        file.write(f"{score}\n")
        for index in indexes:
            start_index = index['startIndex']
            end_index = index['endIndex']
            file.write(f"{start_index} {end_index}\n")

if __name__ == "__main__":
    if len(sys.argv) > 1:
        sentence = sys.argv[1]  # Join arguments into a sentence
        plagarismDetect(sentence)
