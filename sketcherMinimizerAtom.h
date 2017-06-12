/*
 *  sketcherMinimizerAtom.h
 *
 *  Created by Nicola Zonta on 13/04/2010.
 *   Copyright Schrodinger, LLC. All rights reserved.
 *
 */

#ifndef sketcherMINIMIZERATOM_H
#define sketcherMINIMIZERATOM_H

//#include <sketcherMinimizerPointF>
#include <vector>
#include <map>
#include <iostream>

#include "sketcherMinimizerMaths.h"


static const int COORDINATES_LIMIT = 10000000;
static const int INVALID_COORDINATES = COORDINATES_LIMIT + 1;

class sketcherMinimizerBond;

class sketcherMinimizerFragment;
class sketcherMinimizerRing;
class sketcherMinimizerMolecule;

class sketcherMinimizerAtom;
typedef struct {
    sketcherMinimizerAtom* a;
    float priority;
} sketcherMinimizerAtomPriority;

struct CIPAtom {
    CIPAtom(std::vector<std::pair<int, sketcherMinimizerAtom*>> us,
            sketcherMinimizerAtom* dad,
            std::vector<sketcherMinimizerAtom*> allPars,
            std::map<sketcherMinimizerAtom*, int>* scors,
            std::map<sketcherMinimizerAtom*, std::vector<int>>* meds,
            std::map<sketcherMinimizerAtom*, int>* visits

            )
    {
        theseAtoms = us;
        parent = dad;
        scores = scors;
        medals = meds;
        visited = visits;
        allParents = allPars;
    }
    bool operator<(const CIPAtom& rhs) const;
    bool operator==(const CIPAtom& rhs) const;
    bool isBetter(CIPAtom& rhs,
                  std::map<sketcherMinimizerAtom*, unsigned int>* m) const;

    std::vector<std::pair<int, sketcherMinimizerAtom*>>
        theseAtoms; // NULL if dummy
    sketcherMinimizerAtom* parent;
    std::vector<sketcherMinimizerAtom*> allParents;
    std::map<sketcherMinimizerAtom*, int>* scores;
    std::map<sketcherMinimizerAtom*, int>* visited;
    std::map<sketcherMinimizerAtom*, std::vector<int>>* medals;

  private:
    friend std::ostream& operator<<(std::ostream& os, const CIPAtom& a);
};

class  sketcherMinimizerAtom
{
  public:
    sketcherMinimizerAtom()
        : crossLayout(false), fixed(false), constrained(false), rigid(false),
          isSharedAndInner(false), atomicNumber(6), charge(0), _valence(-10),
          _generalUseN(-1), _generalUseN2(-1), m_chmN(-1),
          _generalUseVisited(false), _generalUseVisited2(false), _implicitHs(0),
          fragment(NULL), needsCheckForClashes(false), visited(false),
          coordinatesSet(false), isR(true), hasStereochemistrySet(false),
          _hasRingChirality(false)
    {
        hidden = false;
        m_pseudoZ = 0.f;
        m_pocketDistance = 0.f;
        m_x3D = INVALID_COORDINATES;
        m_y3D = INVALID_COORDINATES;
        m_z3D = INVALID_COORDINATES;
        m_isClashing = false;
        m_isLigand = false;
        m_isWaterMap = false;
        m_clockwiseInvert = false;
        m_isStereogenic = false;
        m_ignoreRingChirality = false;
    };
    virtual ~sketcherMinimizerAtom(){};

    bool crossLayout; // atoms with 4 substituents displayed in a cross style
                      // (such as S in sulphate)
    bool fixed, constrained, rigid;
    bool isSharedAndInner; // shared by two rings and needs to be drawn inside a
                           // ring
    bool hidden;
    int atomicNumber, charge, _valence, _generalUseN, _generalUseN2;
    int m_chmN; // idx of the corresponding ChmAtom if molecule comes from 3d

    bool _generalUseVisited, _generalUseVisited2;
    bool m_clockwiseInvert;
    bool m_ignoreRingChirality;
    std::vector<int> m_RSPriorities;
    unsigned int _implicitHs;
    sketcherMinimizerMolecule* molecule;
    sketcherMinimizerFragment* fragment;
    void setFragment(sketcherMinimizerFragment* fragmentToSet)
    {
        fragment = fragmentToSet;
    }
    sketcherMinimizerFragment* getFragment() const { return fragment; }
    std::vector<sketcherMinimizerBond*> getBonds() const { return bonds; }
    std::vector<sketcherMinimizerRing*> getRings() const { return rings; }
    sketcherMinimizerMolecule* getMolecule() const { return molecule; }

    /*
     Find all connected atoms, pruning the search at the excludedAtom."
     This function assumes that the bond between this atom and excludedAtom
     is not part of a ring.
     */
    std::vector<sketcherMinimizerAtom*>
    getSubmolecule(sketcherMinimizerAtom* excludedAtom);
    std::vector<sketcherMinimizerAtom*> neighbors;
    std::vector<sketcherMinimizerBond*> bonds;
    std::vector<sketcherMinimizerAtom*> residueInteractionPartners;
    std::vector<sketcherMinimizerBond*> residueInteractions;
    std::vector<sketcherMinimizerRing*> rings;
    float m_pseudoZ;

    float m_x3D;
    float m_y3D;
    float m_z3D;

    bool m_isClashing, m_isWaterMap;
    float m_pocketDistance;

    bool needsCheckForClashes;
    bool m_isLigand;
    bool visited, coordinatesSet;
    bool isR; // stereochemistry
    bool hasStereochemistrySet, m_isStereogenic;
    bool _hasRingChirality; // used to keep track of cyclohexane cis/trans
                            // chirality
    void setCoordinates(sketcherMinimizerPointF coords);
    bool hasNoStereoActiveBonds() const;

    sketcherMinimizerPointF getCoordinates() const { return coordinates; }
    int getAtomicNumber() const { return atomicNumber; }
    void setCoordinatesToTemplate() { setCoordinates(templateCoordinates); }
    sketcherMinimizerPointF coordinates;
    sketcherMinimizerPointF templateCoordinates;
    sketcherMinimizerPointF force;
    unsigned int expectedValence(unsigned int atomicNumber) const;
    bool canBeChiral() const; // checks if the atom can have 4 substituents (one
                              // can be implicit H). Doesn't actually check if
                              // two of them are the same, so can return true
                              // for achiral centers

    bool isNeighborOf(sketcherMinimizerAtom* at2) const
    {
        for (unsigned int i = 0; i < at2->neighbors.size(); i++) {
            if (at2->neighbors[i] == this)
                return true;
        }
        return false;
    }

   // bool setStereochemistryFromChmChiralityInfo(ChmChiralityInfo info);

    sketcherMinimizerBond* bondTo(sketcherMinimizerAtom* at) const;

    std::vector<sketcherMinimizerAtom*> clockwiseOrderedNeighbors() const;
    unsigned int findHsNumber() const;

    void writeStereoChemistry(); // assignes up-down bond flags based on isR and
                                 // hasStereochemistrySet
    static bool matchCIPSequence(std::vector<int>& v1, std::vector<int>& v2);
    static bool
    setCIPPriorities(std::vector<sketcherMinimizerAtomPriority>& atomPriorities,
                     sketcherMinimizerAtom* center);
    static void orderAtomPriorities(
        std::vector<sketcherMinimizerAtomPriority>& atomPriorities,
        sketcherMinimizerAtom* center); // orders trying to keep long chains in
                                        // position 2 and 3 and side
                                        // substituents in 1 and 4
    static sketcherMinimizerAtom* CIPPriority(sketcherMinimizerAtom* at1,
                                              sketcherMinimizerAtom* at2,
                                              sketcherMinimizerAtom* center);
    static std::vector<CIPAtom> expandOneLevel(std::vector<CIPAtom>& oldV);
    static void finalizeScores(std::vector<CIPAtom>& v);
    static void assignMedals(std::vector<CIPAtom>& v);
    static void chooseFirstAndSortAccordingly(std::vector<CIPAtom>& V);

    static sketcherMinimizerRing*
    shareARing(const sketcherMinimizerAtom* atom1,
               const sketcherMinimizerAtom* atom2);
    static void mirrorCoordinates(sketcherMinimizerAtom* at,
                                  const sketcherMinimizerBond* bond);

    int readStereochemistry(
        bool readOnly = false); // 0 if not assigned, 1 if R, -1 if S
    sketcherMinimizerPointF getSingleAdditionVector() const;
    static sketcherMinimizerPointF
    getSingleAdditionVector(std::vector<sketcherMinimizerAtom*> ats);
    bool hasValid3DCoordinates() const;
    virtual bool isResidue() const;

    static bool isMetal(const unsigned int atomicNumber);
};

#endif // sketcherMINIMIZERATOM_H
