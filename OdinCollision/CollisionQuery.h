#pragma once
#include "OdinCollision.h"
#include "CollisionResult.h"

namespace OdinCollision {
	template<typename A, typename B>
	class CollisionQuery {
	private:
		A* colliderA;
		B* colliderB;
		std::deque<CollisionResult> results;
		unsigned resultsSize;
	public:
		CollisionQuery(A* colliderA, B* colliderB, unsigned storeResults=100) {
			this->colliderA = colliderA;
			this->colliderB = colliderB;
			query();
			results.resize(storeResults);
			this->resultsSize = storeResults;
		}

		CollisionResult query() {
			CollisionResult result;
			result.insertsecting = intersection<A, B>(colliderA, colliderB);
			result.contained = containment<A, B>(colliderA, colliderB);
			result.seperationDistance = seperation<A, B>(colliderA, colliderB);
			result.overlap = overlap<A, B>(colliderA, colliderB);
			if (results.size()) {
				results.pop_front();
			}
			results.push_back(result);
			return result;
		}
		CollisionResult getLast() {

			return results.back();
		}

		CollisionResult getFirst() {
			return results.front();
		}

		std::vector<CollisionResult> getResults() {
			return vector<CollisionResult>(results.begin(), results.end());

		}

		

		
	};

}
