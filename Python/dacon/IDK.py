# ���̺귯�� ����Ʈ
import pandas as pd
import numpy as np
import torch
from transformers import GPT2LMHeadModel, PreTrainedTokenizerFast, AdamW
from tqdm import tqdm

# CUDA ��� ���� ���� Ȯ��
device = torch.device("cuda" if torch.cuda.is_available() else "cpu")
print(f"Using device: {device}")

# ������ �ε�
data = pd.read_csv("C:/Coding/Python/dacon/train.csv")

# ��ũ������ �ε�
tokenizer = PreTrainedTokenizerFast.from_pretrained('skt/kogpt2-base-v2', eos_token='</s>')

# ������ ������ �� ��ũ����¡
formatted_data = []
for _, row in tqdm(data.iterrows()):
    for q_col in ['����_1', '����_2']:
        for a_col in ['�亯_1', '�亯_2', '�亯_3', '�亯_4', '�亯_5']:
            # ������ �亯 ���� </s> token���� ����
            input_text = row[q_col] + tokenizer.eos_token + row[a_col]
            input_ids = tokenizer.encode(input_text, return_tensors='pt')
            formatted_data.append(input_ids)
print('Done.')

# �� �ε�
model = GPT2LMHeadModel.from_pretrained('skt/kogpt2-base-v2')
model.to(device) # ���� GPU������ �̵�

# �� �н� �������Ķ����(Hyperparameter) ����
# ���� �ʿ信 ���� �����ϼ���.
CFG = {
    'LR' : 2e-5, # Learning Rate
    'EPOCHS' : 10, # �н� Epoch
}

# �� �н� ����
optimizer = AdamW(model.parameters(), lr=CFG['LR'])
model.train()

# �� �н�
for epoch in range(CFG['EPOCHS']):
    total_loss = 0
    progress_bar = tqdm(enumerate(formatted_data), total=len(formatted_data))
    for batch_idx, batch in progress_bar:
        # �����͸� GPU������ �̵�
        batch = batch.to(device)
        outputs = model(batch, labels=batch)
        loss = outputs.loss
        loss.backward()
        optimizer.step()
        optimizer.zero_grad()

        total_loss += loss.item()

        # ����� ǥ���ٿ� ��� �ս� ������Ʈ
        progress_bar.set_description(f"Epoch {epoch+1} - Avg Loss: {total_loss / (batch_idx+1):.4f}")

    # ������ ��� �ս��� ���
    print(f"Epoch {epoch+1}/{CFG['EPOCHS']}, Average Loss: {total_loss / len(formatted_data)}")

# �� ����
model.save_pretrained("./hansoldeco-kogpt2")
tokenizer.save_pretrained("./hansoldeco-kogpt2")

# ����� Fine-tuned �𵨰� ��ũ������ �ҷ�����
model_dir = "./hansoldeco-kogpt2"
model = GPT2LMHeadModel.from_pretrained(model_dir)
model.to(device)
tokenizer = PreTrainedTokenizerFast.from_pretrained(model_dir)

# Inference�� ���� test.csv ���� �ε�
test = pd.read_csv('./test.csv')

# test.csv�� '����'�� ���� '�亯'�� ������ ����Ʈ
preds = []

# '����' �÷��� �� ������ ���� �亯 ����
for test_question in tqdm(test['����']):
    # �Է� �ؽ�Ʈ�� ��ūȭ�ϰ� �� �Է� ���·� ��ȯ
    input_ids = tokenizer.encode(test_question + tokenizer.eos_token, return_tensors='pt')

    # �亯 ����
    output_sequences = model.generate(
        input_ids=input_ids.to(device),
        max_length=300,
        temperature=0.9,
        top_k=1,
        top_p=0.9,
        repetition_penalty=1.2,
        do_sample=True,
    )

# Test �����ͼ��� ��� ���ǿ� ���� �亯���κ��� 512 ������ Embedding Vector ����
# �򰡸� ���� Embedding Vector ���⿡ Ȱ���ϴ� ���� 'distiluse-base-multilingual-cased-v1' �̹Ƿ� �ݵ�� Ȯ�����ּ���.
from sentence_transformers import SentenceTransformer # SentenceTransformer Version 2.2.2

# Embedding Vector ���⿡ Ȱ���� ��(distiluse-base-multilingual-cased-v1) �ҷ�����
model = SentenceTransformer('distiluse-base-multilingual-cased-v1')

# ������ ��� ����(�亯)���κ��� Embedding Vector ����
pred_embeddings = model.encode(preds)

# ���� ��� ����(sample_submission.csv)�� Ȱ���Ͽ� Embedding Vector�� ��ȯ�� ����� ����
submit = pd.read_csv('./sample_submission.csv')
submit.iloc[:,1:] = pred_embeddings

# �������� ������ ���� csv���� ����
submit.to_csv('./baseline_submit.csv', index=False)
