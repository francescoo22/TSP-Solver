import re

def parse_input(input_text):
    # Regular expressions to extract information from input text
    file_pattern = re.compile(r'^\.\./inputs/(\w+)/(\w+_\d+\.dat)$')
    time_pattern = re.compile(r'^Execution time: (\d+) ms$')
    value_pattern = re.compile(r'^Solution value: ([\d.]+)$')

    inputs = input_text.strip().split('\n\n')  # Remove leading/trailing whitespace and split on two newlines
    output = []

    for data in inputs:
        lines = data.strip().split('\n')
        file_match = file_pattern.match(lines[0])
        time_match = time_pattern.match(lines[1])
        value_match = value_pattern.match(lines[2])

        if file_match and time_match and value_match:
            problem_name = file_match.group(1)
            instance_name = file_match.group(2)
            execution_time = int(time_match.group(1))
            solution_value = float(value_match.group(1))

            output.append([instance_name, [solution_value], [execution_time]])

    return output

def read_input_from_file(file_path):
    with open(file_path, 'r') as file:
        input_data = file.read()
    return input_data

n = input("which folder?\n")

# Specify the file path
file_path = f'/home/francesco/Scrivania/Universita/MeMoCO/exam/inputs/tsp{n}/simplex.txt'

# Read input from file
input_data = read_input_from_file(file_path)

# Parse the input and print the output
output = parse_input(input_data)

# Print the output in the desired format
for entry in output:
    print(f"[{entry[0]}], {entry[1]}, {entry[2]},")
