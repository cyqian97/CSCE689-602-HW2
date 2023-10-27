def ProcessRawData(input_file, tag_start_id, tag_max_id = 1482):
    output_file = input_file.split('.')[0]+"_filtered.txt"


    with open(input_file, "r") as input_f, open(output_file, "w") as output_f:
        if "Corel" in input_file:
            for line in input_f:
                if line.startswith('0') or line.startswith('1'):
                    # Remove "," from the line
                    cleaned_line = line.replace(',','')

                    # Filter numbers after the tag_start_id
                    filtered_string = cleaned_line[tag_start_id:]

                    # Write the cleaned line to the output file
                    output_f.write(filtered_string)
        else:
            for line in input_f:
                # Check if the line starts with "@", and if so, skip it
                if line.startswith('{'):                
                    # Remove '{', '}', and ' 1' from the line
                    cleaned_line = line.replace('{', '').replace('}', '').replace(' 1', '').replace('\n','')

                    # Split the string by commas, convert to integers, and filter numbers greater than tag_start_id
                    filtered_numbers = [int(num)-tag_start_id for num in cleaned_line.split(',') if int(num) >= tag_start_id]

                    # Construct 0,1 string from filtered numbers
                    filtered_string = ['0'] * (tag_max_id + 1 - tag_start_id)
                    for i in filtered_numbers:
                        filtered_string[i] = '1'

                    # Write the filter string to the output file
                    output_f.write("".join(map(str, filtered_string))+'\n')
                
    print("Processing complete. Cleaned data saved to", output_file)


if __name__ == "__main__":
    ProcessRawData("datasets/corel16k/Corel16k001.arff", 500)
    ProcessRawData("datasets/corel16k/Corel16k002.arff", 500)
    ProcessRawData("datasets/corel16k/Corel16k003.arff", 500)
    ProcessRawData("datasets/corel16k/Corel16k004.arff", 500)
    ProcessRawData("datasets/corel16k/Corel16k005.arff", 500)
    ProcessRawData("datasets/corel16k/Corel16k006.arff", 500)
    ProcessRawData("datasets/corel16k/Corel16k007.arff", 500)
    ProcessRawData("datasets/delicious/delicious.arff", 500)
