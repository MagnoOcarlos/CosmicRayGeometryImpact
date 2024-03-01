# -*- coding: utf-8 -*-
import pandas as pd #manuseio de dataframes
import numpy as np  #para utilizar arrays e operações matemáticas
import os.path      #teste de existência de arquivos
import sys          #leitura via terminal

#leitura dos dados da simulção isotrópica no CRPropa
data = pd.read_csv(sys.argv[1],header=0, sep = '\s+', dtype ='a')

data = data.astype(float)


#Angulo entre a linha de visada e os ângulos de emissão de cada evento

#produto interno
p_int_px = ( (data.X * data.P0x) + (data.Y * data.P0y) + (data.Z * data.P0z) )

#norma vetor linha divisada
norma_p = np.sqrt( np.power(data.X,2) + np.power(data.Y,2) + np.power(data.Z,2))

#Norma vetor direção de emissão
norma_px = np.sqrt( ( np.power(data.P0x,2) ) + ( np.power(data.P0y,2) )+ ( np.power(data.P0z,2) ) )


ang =  p_int_px / (norma_px * norma_p)

"""
        Criação de uma coluna contendo o angulo entre o vetores
        de emissão e a linha de visada, lembrando que a linha
        de visada varia pra cada pixel dentro do for
 """

data['Ang_linha_de_visada'] = np.degrees( np.arccos( ang ) )


#criando o cone

ang_linha_centro_cone= int(sys.argv[2])
ang_cone=float(sys.argv[4])

sup_ang_cone =ang_linha_centro_cone + ang_cone/2
inf_ang_cone =ang_linha_centro_cone - ang_cone/2

'''
        Apliquei uma ideia de ter o centro do meu cone em relação a linha divisada e subtrair e somar metade do ângulo
        do meu cone a esse ângulo.

'''
test = (data.Ang_linha_de_visada <= sup_ang_cone) & (data.Ang_linha_de_visada >= inf_ang_cone)
cut = data[test]


np.savetxt(sys.argv[3], cut,comments ='', fmt='%f', delimiter="\t", header="D	\tz	\tSN	\tID	\tE\t	X\t	Y\t	Z	\tPx\t	Py\t	Pz\t	SN0\t	ID0\t	E0\t	X0\t	Y0\t	Z0\t	P0x\t	P0y\t	P0z\t	SN1\t	ID1\t	E1\t	X1\t	Y1\t	Z1\t	P1x\t	P1y\t	P1z\t	W\t Ang_linha_de_visada  \t Dist_ang")
