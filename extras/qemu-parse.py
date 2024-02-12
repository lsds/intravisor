import sys
import re
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

def generate_junit_xml(keywords_and_messages, input_text, name, out_path, uptime):
    root = ET.Element("testsuite", name=name)
    
    for keyword, failure_message, should_have_message in keywords_and_messages:
        time="0.0s"
        if "Exited successfully" in keyword:
    	    time=uptime
        if keyword in input_text:
            if should_have_message:
                testcase_element = ET.SubElement(root, "testcase", name=f"{keyword}", time=time)
            else:
                testcase_element = ET.SubElement(root, "testcase", name=f"{keyword}", time=time)
                failure_msg = ET.SubElement(testcase_element, "failure")
                failure_msg.set("message", f"Expected failure message not found: {failure_message}")
        else:
            if should_have_message:
                testcase_element = ET.SubElement(root, "testcase", name=f"{keyword}", time=time)
                failure_msg = ET.SubElement(testcase_element, "failure")
                failure_msg.set("message", f"Expected failure message not found: {failure_message}")
    
    tree = ET.ElementTree(root)
    xml_string = ET.tostring(root, encoding="utf-8")
    decoded_xml = xml_string.decode("utf-8")
    with open(out_path, "w", encoding="utf-8") as file:
        file.write(decoded_xml)

if __name__ == '__main__':
    if len(sys.argv) < 5:
        print("Usage: python script.py <input_file> <keywords_messages_file> <name> <output_file>")
        sys.exit(1)
    
    input_file_path = sys.argv[1]
    keywords_messages_file = sys.argv[2]
    testsuite_name = sys.argv[3]
    output_file_path= sys.argv[4]
    
    try:
        with open(input_file_path, 'r') as input_file:
            input_text = input_file.read()
            pattern = r'Uptime: (?:(\d+)h)?(?:(\d+)m)?(?:(\d+)s)?'
            match = re.search(pattern, input_text)
            total_seconds = "n/a"
            if match:
                hours = int(match.group(1)) if match.group(1) else 0
                minutes = int(match.group(2)) if match.group(2) else 0
                seconds = int(match.group(3)) if match.group(3) else 0

                total_seconds = hours * 3600 + minutes * 60 + seconds
                total_seconds = str(total_seconds)+"s"
#                print(total_seconds)

            KEYWORDS_AND_MESSAGES = load_keywords_messages(keywords_messages_file)
            generate_junit_xml(KEYWORDS_AND_MESSAGES, input_text, testsuite_name, output_file_path,total_seconds)
    except FileNotFoundError:
        print("File not found.")