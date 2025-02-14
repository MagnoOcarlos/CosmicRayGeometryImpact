# -*- coding: utf-8 -*-
"""
Simulacao de propagacao de raios cosmicos com CRPropa3
Autor: Carlos Magno Ribeiro da Costa
Descricao:
    Este script realiza simulacoes de propagacao de raios cosmicos com um campo
    magnetico turbulento, utilizando o pacote CRPropa3.

Parametros:
    - NEvents: Numero de eventos (leitura via argumento de terminal)
    - CoherenceLength: Comprimento de coerencia desejado (em Mpc)
    - Distance: Distancia da fonte (em Mpc)
    - BField: Intensidade do campo magnetico (em nG)

Saida:
    - Arquivos de dados da simulacao com informacoes dos eventos detectados.
"""
import sys
import numpy as np
# from crpropa import (
#     TextOutput, Vector3d, Mpc, Sphere, ModuleList, PropagationBP, PhotoPionProduction,
#     CMB, IRB_Gilmore12, PhotoDisintegration, NuclearDecay, ElectronPairProduction,
#     MinimumEnergy, Redshift, MaximumTrajectoryLength, Grid3f, initTurbulence,
#     MagneticFieldGrid, PeriodicMagneticField, Source, SourcePosition, SourceIsotropicEmission,
#     SourceParticleType, SourcePowerLawSpectrum, ObserverSurface, ObserverNucleusVeto,
#     ObserverPhotonVeto, ObserverElectronVeto, Observer,ObserverNeutrinoVeto, nucleusId,turbulentCorrelationLength,nG,
#     eV, kpc, EeV,IRB_Dominguez11,MinimumEnergyPerParticleId,TeV,SourceUniformRedshift,ObserverRedshiftWindow,EBL_Saldana21
# )

from crpropa import *

def lmax_from_coherence_length(lmin, gridsize, coherence_length):
    n = 1000
    lmaxs = np.logspace(np.log10(lmin), np.log10(gridsize), n)
    lcs = [turbulentCorrelationLength(lmin, lmax, -11 / 3) for lmax in lmaxs]
    return np.interp(coherence_length, lcs, lmaxs)

def setup_output_files(a, z, distance, b_field, coherence_length, seed):
    output_file_cr = f"sim-A_{a}_Z_{z}_R_{distance}_Mpc_B_{b_field}nG_lc_{coherence_length}Mpc_seed{seed}-CR.txt"
    output_file_nu = f"sim-A_{int(a)}_Z_{int(z)}_R_{int(distance)}_Mpc_B_{b_field}nG_lc_{coherence_length}Mpc_seed{seed}-NU.txt"
    return output_file_cr, output_file_nu

def simulate(a, z, n_events, coherence_length, distance, B):
    n_events = n_events 
    energy_range = (0.1 * EeV, 1000 * EeV)
    box_origin = Vector3d(0, 0, 0) * Mpc
    box_size = 10 * Mpc
    neutrinos = True
    photons = electrons = False
    cmb = CMB()
    ebl = IRB_Saldana21()        
    for i in range(1):
        
        
        # Magnetic field setup
        random_seed = i + 1
        space = 0.1 * Mpc
        lmax = lmax_from_coherence_length(space * 2, box_size, coherence_length * Mpc)
        vgrid = Grid3f(box_origin, 200, space)
        initTurbulence(vgrid, B * nG, space * 2, lmax, -11 / 3, random_seed)
        b_field0 = MagneticFieldGrid(vgrid)
        b_field = PeriodicMagneticField(b_field0, Vector3d(4000, 4000, 4000) * Mpc, Vector3d(0), False)

        output_file_cr, output_file_nu = setup_output_files(a, z, distance, B, coherence_length, i)
        
        # Source setup
        source = Source()
        source.add(SourcePosition(Vector3d(0, 0, 0)))
        source.add(SourceIsotropicEmission())
        source.add(SourceParticleType(nucleusId(a, z)))
        source.add(SourceUniformRedshift(0, 1))
        source.add(SourcePowerLawSpectrum(*energy_range, -1.0))

        # Output setup
        output_cr = TextOutput(output_file_cr)
        output_cr.setEnergyScale(eV)
        output_cr.setLengthScale(Mpc)

        output_nu = TextOutput(output_file_nu)
        output_nu.setEnergyScale(eV)
        output_nu.setLengthScale(Mpc)

        # Observer setup
        observer_type = ObserverSurface(Sphere(Vector3d(0, 0, 0), distance * Mpc))
        neutrino_veto = ObserverNeutrinoVeto()
        nucleus_veto = ObserverNucleusVeto()
        photon_veto = ObserverPhotonVeto()
        electron_veto = ObserverElectronVeto()

        observer_cr = Observer()
        observer_cr.add(observer_type)
        observer_cr.add(neutrino_veto)
        observer_cr.add(photon_veto)
        observer_cr.add(electron_veto)
        observer_cr.onDetection(output_cr)
        observer_cr.add(ObserverRedshiftWindow(-0.1,0.1))

        observer_nu = Observer()
        observer_nu.add(observer_type)
        observer_nu.add(nucleus_veto)
        observer_nu.add(photon_veto)
        observer_nu.add(electron_veto)
        observer_nu.onDetection(output_nu)
        observer_nu.add(ObserverRedshiftWindow( -0.1, 0.1))

        #interatctions
        	
        # interactions: photodisintegration
        pd_cmb = PhotoDisintegration(cmb)
        pd_cmb.setHavePhotons(photons)
        pd_ebl = PhotoDisintegration(ebl)
        pd_ebl.setHavePhotons(photons)

        # interactions: photopion production
        ppp_cmb = PhotoPionProduction(cmb)
        ppp_cmb.setHavePhotons(photons)
        ppp_cmb.setHaveElectrons(electrons)
        ppp_cmb.setHaveNeutrinos(neutrinos)
        ppp_ebl = PhotoPionProduction(ebl)
        ppp_ebl.setHavePhotons(photons)
        ppp_ebl.setHaveElectrons(electrons)
        ppp_ebl.setHaveNeutrinos(neutrinos)

        # interactions: Bethe-Heitler pair production
        epp_cmb = ElectronPairProduction(cmb)
        epp_cmb.setHaveElectrons(electrons)
        epp_ebl = ElectronPairProduction(ebl)
        epp_ebl.setHaveElectrons(electrons)

        # decays
        nd = NuclearDecay()
        nd.setHavePhotons(photons)
        nd.setHaveElectrons(electrons)
        nd.setHaveNeutrinos(neutrinos)

        # adiabatic losses
        z = Redshift()

        processes = [pd_cmb, pd_ebl, ppp_cmb, ppp_ebl, epp_cmb, epp_ebl, nd, z]
        propagator=PropagationBP(b_field, 1e-3, 1 * kpc, 10 * kpc)

        # break condition:  
	#  neutrinos: we are studying ~PeV-EeV energies, so E>10 TeV is suitable
        break_energy = MinimumEnergyPerParticleId(0.1 * EeV) # global minimum energy 
        break_energy.add( 12, 10 * TeV) # Electron Neutrino 
        break_energy.add(-12, 10 * TeV) #Eclectron Antineutrino
        break_energy.add( 14, 10 * TeV) #Muon Neutrino
        break_energy.add(-14, 10 * TeV) #Muon Antineutrino
        break_energy.add( 16, 10 * TeV) #Tau Neutrino
        break_energy.add(-16, 10 * TeV) #Tau Antineutrino

        # Simulation setup
        sim = ModuleList()
        for interaction in processes:
            sim.add(interaction)
        
        sim.add(propagator)
        # sim.add(MinimumEnergy(0.01 * EeV))
        sim.add(MaximumTrajectoryLength(4000 * Mpc))
        sim.add(observer_cr)
        sim.add(observer_nu)

        sim.setShowProgress(True)
        sim.run(source, n_events, True)
        
        output_cr.close()
        output_nu.close()

        return output_cr, output_nu

def main():
    if len(sys.argv) != 5:
        print("Uso: python script.py <NEvents> <CoherenceLength[Mpc]> <Distance[Mpc]> <BField[nG]>")
        sys.exit(1)

    n_events = int(sys.argv[1])
    coherence_length = float(sys.argv[2])
    distance = float(sys.argv[3])
    b_field = float(sys.argv[4])

    print(f"Iniciando simulacao com:")
    print(f" - Numero de Eventos: {n_events}")
    print(f" - Comprimento de Coerencia: {coherence_length} Mpc")
    print(f" - Distancia: {distance} Mpc")
    print(f" - Campo Magnetico: {b_field} nG")

    simulate(
        a=1,
        z=1,
        n_events=n_events,
        coherence_length=coherence_length,
        distance=distance,
        B=b_field,
    )

if __name__ == "__main__":
    main()
