# Word Lookup and Plagiarism Detector

## Overview

The **Word Lookup and Plagiarism Detector** is a C++ project developed using Qt Creator. This application provides two main functionalities: checking for plagiarism and reading text with additional linguistic features. 

### Features

1. **Plagiarism Checker**:
   - Utilizes the Govinston.ai API to check for plagiarism in the provided text.
   - Highlights plagiarized text within the document.
   - Displays the plagiarism rate and word count of the text.
   - **Note**: The Govinston.ai API has a limit of 2500 words per request. Users must create an account on the Govinston.ai website to obtain an API token. This token should be placed in the `plagiarism_checker2.py` file under the `"Authorization": "Bearer <token>"` header.

2. **Read Mode**:
   - Displays the total word count and plagiarism rate of the text.
   - Highlights any plagiarized sections.
   - Provides detailed information for each word that is double-clicked, including:
     - Part of Speech
     - Synonyms
     - Example sentence usage
   - This functionality is powered by the PyDictionary and Dictionary API.

## Installation

1. **Clone the Repository**:
   ```bash
   git clone https://github.com/RoshaanH/Word-Lookup-and-Plagiarism-Detector.git
   cd word-lookup-plagiarism-detector
   
  
2. **Set Up the Environment**:
   - Make sure you have Qt Creator installed.
   - Install the required Python packages for the plagiarism checker and dictionary functionalities:
     ```bash
     pip install requests PyDictionary
     ```

3. **Obtain API Token**:
   - Sign up at [Govinston.ai](https://govinston.ai) to get your API token.
   - Open `plagiarism_checker2.py` and replace `<token>` with your actual token:
     ```python
     headers = {
         "Authorization": "Bearer <token>"
     }
     ```

4. **Build the Project**:
   - Open the project in Qt Creator.
   - Build the project using the build options in Qt Creator.

## Usage

1. **Launch the Application**:
   - Run the application from Qt Creator or the compiled executable.

2. **Select Functionality**:
   - Choose between the **Plagiarism Checker** and **Read Mode** from the main menu.

3. **Plagiarism Checker**:
   - Input or paste the text you want to check for plagiarism.
   - Click the "Plagiarism" button to analyze the text.
   - Review the results, including the plagiarism rate and highlighted plagiarized sections.

4. **Read Mode**:
   - Load the text you want to read.
   - Double-Right-click on any word to see its meaning, part of speech, synonyms, and an example sentence.

## Limitations

- The plagiarism detection feature is limited to 2500 words per request due to the Govinston.ai API restrictions.
- Ensure you have a valid API token to use the plagiarism checker without issues.

## Contributing

Contributions are welcome! If you have suggestions for improvements or new features, please open an issue or submit a pull request.

## License

This project is licensed under the MIT License. See the LICENSE file for more details.

## Acknowledgments

- [Govinston.ai](https://govinston.ai) for the plagiarism detection API.
- [PyDictionary](https://pypi.org/project/PyDictionary/) and [DictionaryApi](https://dictionaryapi.dev/) for providing word definitions and synonyms.
- Qt Framework for providing a robust development environment.
