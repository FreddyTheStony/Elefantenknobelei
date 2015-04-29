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
#include <iostream>
#include <vector>
#include <ctime>

#include "Card.h"

//#define ZERO_TEST

/*
Number of cards: 9
Cards: [0,0,0,0]	[0,0,0,0]	[0,0,0,0]	[0,0,0,0]	[0,0,0,0]	[0,0,0,0]	[0,0,0,0]	[0,0,0,0]	[0,0,0,0]
95126814720 solutions found.
1260.4s needed
*/

int main(int argc, char** argv) {
	std::vector<Card> cards;

	std::cout << "legend\n"
			  << "======\n"
			  << "1 = frontal\n"
			  << "2 = head to the right\n"
			  << "3 = ass (back)\n"
			  << "4 = head to the left\n"
			  << "- = lower part\n"
			  << "+ = upper part\n\n";
#ifdef ZERO_TEST
	cards.emplace_back(0,0,0,0);
	cards.emplace_back(0,0,0,0);
	cards.emplace_back(0,0,0,0);
	cards.emplace_back(0,0,0,0);
	cards.emplace_back(0,0,0,0);
	cards.emplace_back(0,0,0,0);
	cards.emplace_back(0,0,0,0);
	cards.emplace_back(0,0,0,0);
	cards.emplace_back(0,0,0,0);
#else
	cards.emplace_back( -2, -4,  1,  3);
	cards.emplace_back( -1, -4,  1,  3);
	cards.emplace_back( -1, -3,  2,  4);
	cards.emplace_back( -2, -3,  2,  4);
	cards.emplace_back( -1,  2,  3, -4);
	cards.emplace_back( -3,  1,  2, -4);
	cards.emplace_back( -3,  2,  4, -1);
	cards.emplace_back( -2, -3,  1,  4);
	cards.emplace_back( -3, -4,  2,  1);
#endif

	int N = cards.size();
	std::cout << "Number of cards: " << N << std::endl;
	std::cout << "Cards: ";
	for (const auto& card : cards) {
		std::cout << card << "\t";
	}
	std::cout << "\n\n";

	bool used[9];
	for (auto& u : used) {
		u = false;
	}

	std::vector<Solution> solutions;

	unsigned long long solution_counter = 0;

	// Cards:
	//  a  b  c
	//  d  e  f
	//  g  h  i
	const RotatedCard *card_a, *card_b, *card_c;
	const RotatedCard *card_d, *card_e, *card_f;
	const RotatedCard *card_g, *card_h, *card_i;

	const clock_t begin_time = std::clock(); // start: measure running time

	// card a
	for (int a = 0; a < N; ++a) {
		used[a] = true;
#ifdef ZERO_TEST
		std::cout << a << " (" << 100.0*a/N << "%)     \r" << std::flush;
#endif
		for (int rot_a = 0; rot_a < 4; rot_a++) {
			card_a = &(cards[a].rot(rot_a));

			// card b
			for (int b = 0; b < N; ++b) {
				if (used[b]) {
					continue;
				}
				used[b] = true;
				for (int rot_b = 0; rot_b < 4; rot_b++) {
					card_b = &(cards[b].rot(rot_b));
					if (card_a->right + card_b->left) {
						continue;
					}

					// card c
					for (int c = 0; c < N; ++c) {
						if (used[c]) {
							continue;
						}
						used[c] = true;
						for (int rot_c = 0; rot_c < 4; rot_c++) {
							card_c = &(cards[c].rot(rot_c));
							if (card_b->right + card_c->left) {
								continue;
							}

							// card d
							for (int d = 0; d < N; ++d) {
								if (used[d]) {
									continue;
								}
								used[d] = true;
								for (int rot_d = 0; rot_d < 4; rot_d++) {
									card_d = &(cards[d].rot(rot_d));
									if (card_a->bottom + card_d->top) {
										continue;
									}

									// card e
									for (int e = 0; e < N; ++e) {
										if (used[e]) {
											continue;
										}
										used[e] = true;
										for (int rot_e = 0; rot_e < 4; rot_e++) {
											card_e = &(cards[e].rot(rot_e));
											if ((card_d->right + card_e->left) || (card_b->bottom + card_e->top)) {
												continue;
											}

											// card f
											for (int f = 0; f < N; ++f) {
												if (used[f]) {
													continue;
												}
												used[f] = true;
												for (int rot_f = 0; rot_f < 4; rot_f++) {
													card_f = &(cards[f].rot(rot_f));
													if ((card_e->right + card_f->left) || (card_c->bottom + card_f->top)) {
														continue;
													}

													// card g
													for (int g = 0; g < N; ++g) {
														if (used[g]) {
															continue;
														}
														used[g] = true;
														for (int rot_g = 0; rot_g < 4; rot_g++) {
															card_g = &(cards[g].rot(rot_g));
															if (card_d->bottom + card_g->top) {
																continue;
															}

															// card h
															for (int h = 0; h < N; ++h) {
																if (used[h]) {
																	continue;
																}
																used[h] = true;
																for (int rot_h = 0; rot_h < 4; rot_h++) {
																	card_h = &(cards[h].rot(rot_h));
																	if ((card_g->right + card_h->left) || (card_e->bottom + card_h->top)) {
																		continue;
																	}

																	//card i
																	for (int i = 0; i < N; ++i) {
																		if (used[i]) {
																			continue;
																		}
																		used[i] = true;
																		for (int rot_i = 0; rot_i < 4; rot_i++) {
																			card_i = &(cards[i].rot(rot_i));
																			if ((card_h->right + card_i->left) || (card_f->bottom + card_i->top)) {
																				continue;
																			}

#ifndef ZERO_TEST
																			// everything fits!!!
																			solutions.push_back(Solution(a+1,rot_a, b+1,rot_b, c+1,rot_c,
																										 d+1,rot_d, e+1,rot_e, f+1,rot_f,
																										 g+1,rot_g, h+1,rot_h, i+1,rot_i));

#endif
																			solution_counter++;
																		} // rot_i
																		used[i] = false;
																	} // i
																} // rot_h
																used[h] = false;
															} // h
														} // rot_g
														used[g] = false;
													} // g
												} // rot_f
												used[f] = false;
											} // f
										} // rot_e
										used[e] = false;
									} // e
								} // rot_d
								used[d] = false;
							} // d
						} // rot_c
						used[c] = false;
					} // c
				} // rot_b
				used[b] = false;
			} // b
		} // rot_a
		used[a] = false;
	} // a

	std::cout << float( std::clock () - begin_time ) /  CLOCKS_PER_SEC << "s needed\n"; // end: measure running time

	/*
	for (const auto& solution : solutions) {
		std::cout << solution << "\n";
	}
	*/
	std::cout << solution_counter << " solutions (possibly pairwise equivalent) found.\n" << std::endl;

	// group pairwise equivalent solutions (only rotated against each other)
	// =====================================================================
	std::vector<std::vector<Solution> > paired_solutions{};

	std::vector<Solution> solution_group;
	while (!solutions.empty()) {
		Solution ref = solutions[0];		// reference solution for this group
		solutions.erase(solutions.begin()); // delete first element (reference solution)
		solution_group.clear(); 			// new solution group
		solution_group.push_back(ref); 		// reference solution is the first element of the new group
		// search for equivalent solutions to reference solution
		unsigned int index = 0;
		while (index < solutions.size()) {
			while (index < solutions.size() && ref.is_same_as(solutions[index])) {
				solution_group.push_back(solutions[index]);
				solutions.erase(solutions.begin()+index);
			}
			index++;
		}
		// add group to vector
		paired_solutions.push_back(solution_group);
	}

	// print paired solutions
	// ======================
	int num = 1;
	for (const auto& solution_vec : paired_solutions) {
		std::cout << "solution #" << num << "\n";
		for (const auto& solution : solution_vec) {
			std::cout << solution << "\n";
		}
		num++;
	}
	std::cout << paired_solutions.size() << " (different) solutions found.\n";

	return 0;
}
