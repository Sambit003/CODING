import openai

openai.api_key = "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"

while True:
    response = openai.ChatCompletion.create(
    model="gpt-3.5-turbo",
        messages=[
            {
            "role": "system",
            "content": "1. You'll be given with a java quiz which includes the question and the code block. Suppose someone got stuck and not understanding the question and you should provide the hint. \nNow, don't return the output of that particular code block. Just give them some other hints. For just the kickstart. \n\n2. You'll be given with a java related question. Just return the answer of that query\n\n3. Don't answer any other questions "
            },
            {
            "role": "user",
            "content": "Ok"
            },
        ],
        temperature=0.01,
        max_tokens=256,
        top_p=1,
        frequency_penalty=0,
        presence_penalty=0
    )

    print(response)

