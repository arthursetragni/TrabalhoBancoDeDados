## Trabalho de Banco de Dados

### Criação das Tabelas SQL

1. **Tabela Ambulatório:**
   
```sql
CREATE TABLE Ambulatorio (
    numeroA INT PRIMARY KEY,
    andar INT NOT NULL,
    capacidade INT NOT NULL
);
```

2. **Tabela Médico:**
   
```sql
CREATE TABLE Medico (
    CRM INT PRIMARY KEY,
    nome VARCHAR(100) NOT NULL,
    idade INT NOT NULL,
    cidade VARCHAR(100) NOT NULL,
    especialidade VARCHAR(100) NOT NULL,
    numeroA INT,
    FOREIGN KEY (numeroA) REFERENCES Ambulatorio(numeroA)
);
```

3. **Tabela Paciente:**
   
```sql
CREATE TABLE Paciente (
    RG INT PRIMARY KEY,
    nome VARCHAR(100) NOT NULL,
    idade INT NOT NULL,
    cidade VARCHAR(100) NOT NULL,
    doenca VARCHAR(100) NOT NULL
);
```

4. **Tabela Consulta:**
   
```sql
CREATE TABLE Consulta (
    CRM INT,
    RG INT,
    data DATE NOT NULL,
    hora TIME NOT NULL,
    PRIMARY KEY (CRM, RG),
    FOREIGN KEY (CRM) REFERENCES Medico(CRM),
    FOREIGN KEY (RG) REFERENCES Paciente(RG)
);
```

5. **Tabela Funcionário:**
   
```sql
CREATE TABLE Funcionario (
    RG INT PRIMARY KEY,
    nome VARCHAR(100) NOT NULL,
    idade INT NOT NULL,
    cidade VARCHAR(100) NOT NULL,
    salario DECIMAL(10,2) NOT NULL
);
```

### Importação de Arquivos CSV

Para testar as consultas SQL, foram gerados arquivos CSV para preencher as tabelas com dados fictícios. Os arquivos CSV e os scripts de importação podem ser encontrados no diretório `data`.

1. **Arquivo `ambulatorios.csv`:** Contém dados para a tabela Ambulatório.
2. **Arquivo `medicos.csv`:** Contém dados para a tabela Médico.
3. **Arquivo `pacientes.csv`:** Contém dados para a tabela Paciente.
4. **Arquivo `consultas.csv`:** Contém dados para a tabela Consulta.
5. **Arquivo `funcionarios.csv`:** Contém dados para a tabela Funcionário.
