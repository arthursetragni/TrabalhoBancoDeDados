-- /*Consultas SQL requeridas*/
-- 1) buscar os dados dos pacientes que estão com dengue

Select * from Paciente where doenca = "dengue";

-- 2) buscar os dados dos médicos cardiologistas com mais de 44 anos

Select * from Medico where especialidade = "cardiologista" and idade > 44;

-- 3) buscar os dados das consultas, exceto aquelas marcadas para os médicos com CRM 4656 e 1879

Select * from Consulta where crm <> 4656 and crm <> 1879;

-- 4) buscar os dados dos ambulatórios do quarto andar que ou tenham capacidade igual a 50 ou tenham número superior a 10

Select * from Ambulatorio where andar = 4 or capacidade = 50 or numeroA > 10;

-- 5) buscar o nome e a especialidade de todos os médicos

SELECT nome, especialidade FROM Medico;

-- 6) buscar os números dos ambulatórios, exceto aqueles do segundo e quarto andares, que suportam mais de 50 pacientes

SELECT * from Ambulatorio where capacidade > 50 and (andar <> 2 and andar <> 4);

-- 7) buscar o nome dos médicos que têm consulta marcada e as datas das suas consultas

SELECT Medico.nome, Consulta.data FROM Medico INNER JOIN Consulta ON Medico.CRM = Consulta.CRM;

-- 8) buscar o número e a capacidade dos ambulatórios do quinto andar e o nome dos médicos que atendem neles

SELECT Ambulatorio.numeroA, Ambulatorio.capacidade, Medico.nome
From Ambulatorio inner join Medico where Medico.numeroA = Ambulatorio.numeroA and Ambulatorio.andar = 5; 

-- 9) buscar o nome dos médicos e o nome dos seus pacientes com consulta marcada, assim como a data destas consultas

SELECT Medico.nome AS nome_medico, Paciente.nome AS nome_paciente, Consulta.data
FROM Medico
INNER JOIN Consulta ON Medico.CRM = Consulta.CRM
INNER JOIN Paciente ON Paciente.RG = Consulta.RG;

-- 10) buscar os nomes dos médicos ortopedistas com consultas marcadas para o período da manhã (7hs-12hs) do dia 20/06/24

Select Medico.nome
from Medico 
inner join Consulta
on Consulta.data = "2024-06-24" and Consulta.hora > "07:00" and Consulta.hora < "12:00" and Medico.CRM = Consulta.CRM;

-- 11) buscar os nomes dos pacientes, com consultas marcadas para os médicos João Carlos Santos ou Maria Souza, que estão com pneumonia

Select Paciente.nome from Paciente
inner join Consulta	on Paciente.RG = Consulta.RG and Paciente.doenca = "pneumonia"
Inner join Medico on Medico.CRM = Consulta.CRM and (Medico.nome = "João Carlos Santos" or Medico.nome = "Maria Souza");


-- 12) buscar os nomes dos médicos e pacientes cadastrados no hospital

Select Paciente.nome as nome from Paciente
Union
Select Medico.nome as nome from Medico;

-- 13) buscar os nomes e idade dos médicos, pacientes e funcionários que residem em Ribeirão das Neves

Select Paciente.nome as nome, Paciente.idade as idade from Paciente where Paciente.cidade = "Ribeirão das Neves"
Union
Select Funcionario.nome as nome, Funcionario.idade as idade from Funcionario where Funcionario.cidade = "Ribeirão das Neves"
Union 
Select Medico.nome as nome, Medico.idade as idade from Medico where Medico.cidade = "Ribeirão das Neves";

-- 14) buscar os nomes e RGs dos funcionários que recebem salários abaixo de R$ 3000,00 e que não estão internados como pacientes

-- 15) buscar os números dos ambulatórios onde nenhum médico dá atendimento

-- 16) buscar os nomes e RGs dos funcionários que estão internados como pacientes

-- 17) excluir todos os funcionarios que residem em Contagem

-- 18) alterar o ambulatório de todos os médicos neurologistas para o andar 2.

-- 19) desmarcar todas as consultas do mês de outubro do médico Vitor Miranda

-- 20) transferir as consultas do médico José Carlos do dia 15 julho para o dia 20 de setembro