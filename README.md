# EvolutionaryArt

Project for the coruse of Fondamenti di Intelligenza Artificiale.
This work was based on [NEvAr](https://www.researchgate.net/publication/2244120_NEvAr_--_The_Assessment_of_an_Evolutionary_Art_Tool)

Developed in Visual studio. Uses [wxWidgets](https://www.wxwidgets.org/) and [FastNoiseLite](https://github.com/Auburn/FastNoiseLite) for cpp.

## Main features

- Interactive software that allows an user to create art generated with genetic algorithms
- Individuals are composed of arithmetic, mathematical and trigonometric functions, and noise generators
- The users give a score to an Individual from 1 to 10
- Standard evolutionary alghorithm is applied:
    - A fitness proportionate selection chooses the parents
    - Crossover between the parents to generate the children
    - 80% chance of mutation on the children
    - Display the new generation
- A filter on the genotype is applied to discard the Individual that have no aesthetic value.
- The 10/10 individuals of previous generation are "frozen" and can be injected in the current generation in the place of a chosen Individual
    - Allows to escape local optima
    - Allows the user to remove Individuals that are too noisy in place of better ones
    - The user could think about combinations that can give interesting results