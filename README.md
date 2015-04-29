# Elefantenknobelei

/**
 * @brief
 * Brute force generator to find solutions of the puzzle "Elefantenknobelei"
 *
 * The goal of this puzzle is to arrage 9 cards with pictures of elephants in that way that the pictures fit on every edge of every card.
 * There are four different pictures and every edge contains either the lower or the upper part of the picture.
 * That is a total of 8 different picture "fragments".
 * Considering every possible combination there would be \factorial{9} (positions) \times \pow{4,9} (rotations) = 95126814720 combinations!
 * Luckily most of the combinations can be pruned as the pictures don't fit, reducing the effective number of combinations to be considered drastically.
 *
 * @author Frederic A. Stein
 */
