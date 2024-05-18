namespace ConfigurationManagement
{
    public class ConfigurationLoader
    {
        static Dictionary<string, object> ParseJson(string jsonString)
        {


            // Remove whitespace and newline characters
            jsonString = jsonString.Replace(" ", "").Replace("\n", "").Replace("\r", "").Replace("\t", "");

            // Create a dictionary to store key-value pairs
            Dictionary<string, object> result = new Dictionary<string, object>();

            // Stack to handle nested objects
            Stack<Dictionary<string, object>> stack = new Stack<Dictionary<string, object>>();
            stack.Push(result);

            // Temporary variables for parsing
            string key = null;
            bool inString = false;
            bool inEscape = false;

            // Iterate over characters in the JSON string
            for (int i = 0; i < jsonString.Length; i++)
            {
                char c = jsonString[i];

                // Handle strings
                if (c == '"' && !inEscape)
                {
                    inString = !inString;
                }

                // Handle escapes
                if (c == '\\' && inString)
                {
                    inEscape = !inEscape;
                }
                else
                {
                    inEscape = false;
                }

                // Handle key-value pairs
                if (c == ':' && !inString)
                {
                    key = jsonString.Substring(0, i);
                    // Remove quotes from the key
                    key = key.Trim('"');
                    jsonString = jsonString.Substring(i + 1).Trim();
                    i = -1; // Reset index for the next iteration
                }

                // Handle nested objects
                if (c == '{' && !inString)
                {
                    Dictionary<string, object> nested = new Dictionary<string, object>();
                    stack.Peek().Add(key, nested);
                    stack.Push(nested);
                    jsonString = jsonString.Substring(i + 1).Trim();
                    i = -1; // Reset index for the next iteration
                }

                // Handle nested objects closing
                if (c == '}' && !inString)
                {
                    stack.Pop();
                    jsonString = jsonString.Substring(i + 1).Trim();
                    i = -1; // Reset index for the next iteration
                }

                // Handle arrays
                if (c == '[' && !inString)
                {
                    jsonString = jsonString.Substring(i + 1).Trim();
                    i = -1; // Reset index for the next iteration
                }

                if (c == ']' && !inString)
                {
                    jsonString = jsonString.Substring(i + 1).Trim();
                    i = -1; // Reset index for the next iteration
                }
            }

            return result;
        }

        static object GetValueForKey(Dictionary<string, object> jsonDict, string key)
        {

            // Split the key into parts if it's nested
            string[] keyParts = key.Split('.');

            // Start from the root dictionary
            object value = jsonDict;

            // Traverse through the nested structure
            foreach (var part in keyParts)
            {
                // Check if the current value is a dictionary
                if (value is Dictionary<string, object> dict)
                {
                    // Check if the current part exists as a key
                    if (dict.ContainsKey(part))
                    {
                        // Move to the next nested level
                        value = dict[part];
                    }
                    else
                    {
                        // Key does not exist
                        Console.WriteLine($"Key '{key}' not found.");
                        return null;
                    }
                }
                else
                {
                    // Key is not nested, so no further traversal is possible
                    Console.WriteLine($"Key '{key}' is not nested.");
                    return null;
                }
            }

            // Return the value associated with the final key
            return value;
        }
    }
}