## Trabalho de Banco de Dados

Na pasta `programasGeradores` estão programas em C usados para gerar os arquivos CSV.

Na pasta `tabelasCSV` estão os arquivos CSV prontos para serem importados no MySqlWorkbench.

O arquivo `scriptCriacaoDasTabelas.sql` contém os scripts para a geração das tabelas SQL.

E o arquivo `scriptDeConsultas.sql` contém todos os scripts SQL de consultas pedidos pelo professor.

As consultas em **álgebra relacional** estão listadas ao final deste `README.md`.

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

### Consultas em Álgebra Relacional

Para adequação ao modelo matemático, os dados originalmente de tipo `date`, foram representativamente convertidos para um tipo numérico. Desse modo, a data `DD/MM/YYYY HH:mm:ss` pôde ser manipulada pelos operadores nativos da álgebra relacional enquanto valor numérico `YYYYMMDDHHmmss`, tal que `31/12/2024 23h59m00s` corresponde a `20241231235900`, segundo a fórmula:

$$
Date = (YYYY \times 10^{10}) + (MM \times 10^8) + (DD \times 10^6) + (HH \times 10^4) + (mm \times 10^2) + ss
$$

As consultas em álgebra relacional abaixo foram geradas apenas a partir das operações de busca listadas no enunciado (***consultas de 01 a 16***), se atendo às restrições do modelo.

1) **Buscar os dados dos pacientes que estão com dengue**
```
π rg,nome,idade,cidade,doenca (σ doenca = 'dengue' (Paciente))
```

2) **Buscar os dados dos médicos cardiologistas com mais de 44 anos**
```
π crm,nome,idade,cidade,especialidade,numeroA (
	σ especialidade = 'cardiologista' ∧ idade < 19801231235959 (Medico)
)
```

3) **Buscar os dados das consultas, exceto aquelas marcadas para os médicos com CRM 4656 e 1879**
```
π crm,rg,data,hora (σ crm != 4656 ∧ crm != 1879 (Consulta))
```

4) **Buscar os dados dos ambulatórios do quarto andar que ou tenham capacidade igual a 50 ou tenham número superior a 10**
```
π numeroA,andar,capacidade (
    σ andar = 4 ∨ capacidade = 50 ∨ numeroA > 10 (Ambulatorio)
)
```

5) **Buscar o nome e a especialidade de todos os médicos**
```
π nome,especialidade (Medico)
```

6) **Buscar os números dos ambulatórios, exceto aqueles do segundo e quarto andares, que suportam mais de 50 pacientes**
```
π numeroA (σ andar != 2 ∧ andar != 4 ∧ capacidade > 50 (Ambulatorio))
```

7) **Buscar o nome dos médicos que têm consulta marcada e as datas das suas consultas**
```
π nome,data (
    (ρ m_crm←crm (Medico)) ⨝ m_crm = crm (Consulta)
)
```

8) **Buscar o número e a capacidade dos ambulatórios do quinto andar e o nome dos médicos que atendem neles**
```
π numeroA,capacidade,nome (
    (σ andar = 5 (Ambulatorio)) ⨝ numeroA = m_numeroA (
        (ρ m_numeroA←numeroA (Medico))
    )
)
```

9) **Buscar o nome dos médicos e o nome dos seus pacientes com consulta marcada, assim como a data destas consultas**
```
π nome,p_nome,data (
    (
        (ρ m_crm←crm(Medico)) ⟖ m_crm = crm (ρ c_rg←rg(Consulta))
    ) ⨝ c_rg = rg (ρ p_nome←nome (Paciente))
)
```

10) **Buscar os nomes dos médicos ortopedistas com consultas marcadas para o período da manhã (7hs-12hs) do dia 20/06/24**
```
π nome (
    (ρ m_crm←crm (π nome,crm (
        σ especialidade = 'Ortopedista' (Medico)
    ))) ⨝ m_crm = crm (π crm (
        σ data < 20240620120000 ∧ data < 20240620070000 (Consulta)
    ))
)
```

11) **Buscar os nomes dos pacientes, com consultas marcadas para os médicos João Carlos Santos ou Maria Souza, que estão com pneumonia**
```
π nome (
    (((π m_nome,crm (
        σ m_nome = 'João Carlos Santos' ∨ m_nome = 'Maria Souza' (
            ρ m_nome←nome (Medico)
        )
    )) ⨝ crm = c_crm (ρ c_crm←crm (Consulta))) ⨝ rg = p_rg (
        ρ p_rg←rg (Paciente)
    ))
)
```

12) **Buscar os nomes dos médicos e pacientes cadastrados no hospital**
```
(π nome (Medico)) ∪ (π nome (Paciente))
```

13) **Buscar os nomes e idade dos médicos, pacientes e funcionários que residem em Ribeirão das Neves**
```
(π nome,idade (σ cidade = 'Ribeirao das Neves' (Funcionario)))
∪
(π nome,idade (σ cidade = 'RibeiraodasNeves' (Medico)))
∪
(π nome,idade (σ cidade = 'Ribeirao das Neves' (Paciente)))
```

14) **Buscar os nomes e RGs dos funcionários que recebem salários abaixo de R$ 3000,00 e que não estão internados como pacientes**
```
π nome,rg (
    σ salario < 3000 (ρ f_rg←rg (Funcionario) ⨝ f_rg = rg (
        π rg (Funcionario) - π rg (Paciente)
    ))
)
```

15) **Buscar os números dos ambulatórios onde nenhum médico dá atendimento**
```
π numeroA ((π numeroA (Ambulatorio)) - (π numeroA (Medico)))
```

16) **Buscar os nomes e RGs dos funcionários que estão internados como pacientes**
```
π rg ((ρ f_rg←rg (Funcionario)) ⨝ f_rg = rg (Paciente))
```
