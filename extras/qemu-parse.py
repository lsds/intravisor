import sys
import xml.etree.ElementTree as ET

def load_keywords_messages(file_path):
    keywords_messages = []
    with open(file_path, 'r') as file:
        for line in file:
            keyword, message, should_have_message = line.strip().split(',')
            keyword = keyword[1:-1] 
            message = message[1:-1] 
            keywords_messages.append([keyword, message, should_have_message.lower() == 'true'])
    return keywords_messages

def generate_junit_xml(keywords_and_messages, input_text, name):
    root = ET.Element("testsuite", name=name)
    
    for keyword, failure_message, should_have_message in keywords_and_messages:
        if keyword in input_text:
            if should_have_message:
                testcase_element = ET.SubElement(root, "testcase", name=f"{keyword}")
            else:
                testcase_element = ET.SubElement(root, "testcase", name=f"{keyword}")
                failure_msg = ET.SubElement(testcase_element, "failure")
                failure_msg.set("message", f"Expected failure message not found: {failure_message}")
        else:
            if should_have_message:
                testcase_element = ET.SubElement(root, "testcase", name=f"{keyword}")
                failure_msg = ET.SubElement(testcase_element, "failure")
                failure_msg.set("message", f"Expected failure message not found: {failure_message}")
    
    tree = ET.ElementTree(root)
    xml_string = ET.tostring(root, encoding="utf-8")
    print(xml_string.decode("utf-8"))

if __name__ == '__main__':
    if len(sys.argv) < 4:
        print("Usage: python script.py <input_file> <keywords_messages_file> <name>")
        sys.exit(1)
    
    input_file_path = sys.argv[1]
    keywords_messages_file = sys.argv[2]
    testsuite_name = sys.argv[3]
    
    try:
        with open(input_file_path, 'r') as input_file:
            input_text = input_file.read()
            KEYWORDS_AND_MESSAGES = load_keywords_messages(keywords_messages_file)
            generate_junit_xml(KEYWORDS_AND_MESSAGES, input_text, testsuite_name)
    except FileNotFoundError:
        print("File not found.")