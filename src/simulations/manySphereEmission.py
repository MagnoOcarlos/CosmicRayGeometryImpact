# -*- coding: utf-8 -*-
import sys
import numpy as np
from crpropa import *


def lmaxFromCohrenceLength(lmin, gridsize, compCoerencia):
	
	n=1000
	lmaxs=np.logspace(np.log10(lmin), np.log10(gridsize), n)

	lcs= [ turbulentCorrelationLength(lmin,lmax,-11/3) for lmax in lmaxs ]
	

	return	np.interp(compCoerencia, lcs,lmaxs)
	
	
NEvents = int(sys.argv[1]) #números de eventos lidos via terminal
OutputName = 'dados.txt'
#supre = 'supression.txt'
A =1 #massa atômica
Z =1 #número atômico


#Volume da simulação

'''
	Aqui criamos uma 'caixa' na qual o ocorrerá a nossa simulação. Sendo mais específico, é a região na qual nosso campo mag-
	nético atua.
'''

boxOrigin = Vector3d(0, 0, 0) * Mpc
boxSize = 10 * Mpc
boxEdge = Vector3d(boxSize, boxSize, boxSize)



#Campo Magnético

'''
	Aqui vamos criar o campo magnético da simulação. Tratando-se de uma simualção 3d, usasse o Vector grid para guardar a infor-
	mações dos campo nos eixos (x,y,z) (usando a função VectorGrid)
	
	VectorGrid: o primeiro parâmetro da função é a origem da caixa de atuação do campo; o segundo é o número de células que irão
	preencer essa caixa ( pense num tabuleiro de xadrez em 3d); o terceiro é o tamanho de cada 'casa' desse tabuleiro de xadrez.

	initTurbulence: Essa função inicizaliza um campo turbulento aleatório. Seus parâmetro 
		
		1°: vgrid-> é a grid inicializada com a Função VectorGrid
		2°: módulo do nosso campo magnético
		3°: lmin-> comprimento de onda  mínimo de oscilação turbulenta.
		4°: lmx-> comprimento de onda máximo de oscilação turbulenta.
		5°: índice da lei de potência( nesse caso temos o espectro de Kolmogorov)
		5°: seed 
'''



randomSeed = 42
space = 0.1*Mpc
lmax=lmaxFromCohrenceLength(space*2,boxSize,int(sys.argv[2])*Mpc) # gere o comprimento máximo ideal para o CL desejado
vgrid = VectorGrid(boxOrigin, 1024, space)
initTurbulence(vgrid, 10*nG, space*2, lmax, -11/3, randomSeed)
bField0 = MagneticFieldGrid(vgrid)


#Info

'''
	Print de algumas informações do nosso campo.

'''
'''
print("lmax={} e lmin={}".format(lmax/kpc,2*space/Mpc))
print ("Lc = {}kpc".format(turbulentCorrelationLength( 2*space, lmax , -11./3.)/Mpc))  # correlation length
print ("sqrt(<B^2>) = {} nG".format((rmsFieldStrength(vgrid) / nG)))   # RMS
print ("<|B|> = {} nG".format((meanFieldStrength(vgrid) / nG)) ) # mean
print ("B(10 Mpc, 0, 0) ={}nG".format(bField0.getField(Vector3d(10,0,0) * Mpc) / nG))


'''

#Observador

'''
	A ideia de simulação é fazer uma geometria reversa na qual iremos posicionar a fonte dentro de uma esfera de raio R(distância
	da fonte desejada até a terra). Nesta simulação, a fonte é CenA que está a uma distância de 3.7 Mpc da terra.

	A esfera em questão é a Terra.

	As funções nessa região são intuitivas.
'''


# module setup
sim = ModuleList()
#sim.add(SimplePropagation())
sim.add(PropagationBP(bField0,1e-3,1*kpc,10*kpc))
sim.add(PhotoPionProduction(CMB))
sim.add(PhotoPionProduction(IRB_Gilmore12))
sim.add(PhotoDisintegration(CMB))
sim.add(PhotoDisintegration(IRB_Gilmore12))
sim.add(NuclearDecay())
sim.add(ElectronPairProduction(CMB))
sim.add(ElectronPairProduction(IRB_Gilmore12))
sim.add(MinimumEnergy(0.01 * EeV))
sim.add(Redshift())
sim.add(MaximumTrajectoryLength(4000 * Mpc))

rmax=80
r=0

while r<=rmax:

	out = TextOutput("../geometry/dados_radius_"+str(r)+"_Mpc_many_sphere.txt")
	obs = Observer()
	if r ==0:
		obs.add((ObserverSurface( Sphere(Vector3d(0,0,0), 3.7*Mpc)) ))
	
	else:
		
		obs.add((ObserverSurface( Sphere(Vector3d(0,0,0), r*Mpc)) ))
	if r != 80:	
		obs.setDeactivateOnDetection(False)
	
	obs.onDetection(out)
	sim.add(obs)
	r+=20
	

#fonte


'''
	A fonte irá emitir somente prótons isotropicamente. A energia de emissão varia de 1e17 até 1e21
'''
sourceList = SourceList()
source = Source()
source.add(SourcePosition(Vector3d(0, 0, 0)))
source.add(SourceIsotropicEmission())
source.add(SourcePowerLawSpectrum(1e17 * eV, 1e21 * eV, -1.))
source.add(SourceParticleType(nucleusId(A,Z)))
sourceList.add(source, 1)



c = sourceList.getCandidate()

#execute
sim.setShowProgress(True)
sim.run(sourceList, NEvents, True)
