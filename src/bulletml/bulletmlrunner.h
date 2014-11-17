//BulletML Stuff.
//Attempted Japanese -> English translation courtesy of Google Translate

/**
 * Implement some of the pure virtual functions by inheriting BulletMLRunner
 */

#ifndef BULLETRUNNER_H_
#define BULLETRUNNER_H_

#include "bulletmltree.h"
#include "bulletmlcommon.h"

#include <vector>
#include <boost/smart_ptr.hpp>

class BulletMLParser;
class BulletMLNode;
class BulletMLRunnerImpl;

typedef std::vector<double> BulletMLParameter;

//Class BulletMLRunner uses to transfer states
class BulletMLState {
public:
	DECLSPEC BulletMLState(BulletMLParser* bulletml,
						   const std::vector<BulletMLNode*>& node,
						   boost::shared_ptr<BulletMLParameter> para)
		: bulletml_(bulletml), node_(node.begin(), node.end()), para_(para) {}

	DECLSPEC BulletMLParser* getBulletML() { return bulletml_; }
	DECLSPEC const std::vector<BulletMLNode*>& getNode() const { return node_; }
	DECLSPEC boost::shared_ptr<BulletMLParameter> getParameter() { return para_; }

private:
	BulletMLParser* bulletml_;
	std::vector<BulletMLNode*> node_;
	boost::shared_ptr<BulletMLParameter> para_;

};

//Classes that perform BulletML
/**
 *	1. Inherit this class to create a class which actually moves a Bullet
 *	2. I implement all the pure virtual funtions
 *	3. Implement any virtual functions you need, such as changeDirection()
 *	4. 
 */

class BulletMLRunner {
public:
	DECLSPEC explicit BulletMLRunner(BulletMLParser* bulletml);
    DECLSPEC explicit BulletMLRunner(BulletMLState* state);
    DECLSPEC virtual ~BulletMLRunner();

    DECLSPEC void run();

public:
	/**
	 * @return true if execution has completed
	 *//
	DECLSPEC bool isEnd() const;

public:
	// ------ Begin the set of function which must be implemented ------

	/**
	 * Get the angle of the bullet
	 * @return the angle in degrees 
	 */
	DECLSPEC virtual double getBulletDirection() =0;
	/**
	 * Get the angle that the aircraft is is aiming
	 * @return the angle of the bullet
	 */
	DECLSPEC virtual double getAimDirection() =0;
	/**
	 * @return the velocity of the bullet
	 */
	DECLSPEC virtual double getBulletSpeed() =0;
	/**
	 * @return the default velocity of the bullet
	 */
	DECLSPEC virtual double getDefaultSpeed() =0;
	/**
	 * Get the rank (what the hell is rank?)
	 * @return real number in interval [0,1]
	 */
	DECLSPEC virtual double getRank() =0;
	/**
	 * Make the bullet without an action
	 */
	DECLSPEC virtual void createSimpleBullet(double direction, double speed) =0;
	/**
	 * Make the bullet without an action (not sure what this means...)
	 * @param state, to be passed into the ctor of the new bullet BulletMLRunner.
	 * If you'd rather it not be passed, you must free it with delete.
	 */
	DECLSPEC virtual void createBullet(BulletMLState* state, double direction, double speed) =0;
	/// 弾の基準となるターンの値を返す、通常はフレーム数
	/**
	 * @return
	 * ゲームごとの基準でオーダーは変更して構いませんが、
	 * 負数は許されません。
	 * xml データ上で、wait と term のオーダーが揃っていれば問題ありません。
	 */
	DECLSPEC virtual int getTurn() =0;
	// Die, apparently :(
	DECLSPEC virtual void doVanish() =0;
	// -----The end of the functions that must be implemented -----

	// ----- Beginning of the functions which can be implemented if need be -----

	/**
	 * Change the direction of the bullet
	 */
	DECLSPEC virtual void doChangeDirection(double) {}
	/**
	 * Change the speed of the bullet
	 */
	DECLSPEC virtual void doChangeSpeed(double) {}
	/// accel に対するインターフェイス
	/**
	 * @todo
	 * Horizontal, vertical, type
	 * どれも absolute になってしまいます。
	 */
	DECLSPEC virtual void doAccelX(double) {}
	/// accel に対するインターフェイス
	/**
	 * @todo
	 * horizontal, vertical の type は未実装です。
	 * どれも absolute になってしまいます。
	 */
	DECLSPEC virtual void doAccelY(double) {}
	/**
	 * @return the speed in the x direction
	 * @note Override if you wish to use the accel methods
 	 */
	DECLSPEC virtual double getBulletSpeedX() { return 0; }
	/**
	 * @return the speed in the y direction
	 * @note Override if you wish to use the accel methods
 	 */
	DECLSPEC virtual double getBulletSpeedY() { return 0; }

	// ----- End of functions which can be overridden if need be -----

	/**
	 * @return a random number
	 */
	DECLSPEC virtual double getRand() { return (double)rand() / RAND_MAX; }

private:
	// Override this if you want to override the BulletMLRunnerImpl
	DECLSPEC virtual BulletMLRunnerImpl* makeImpl(BulletMLState* state);

protected:
	std::vector<BulletMLRunnerImpl*> impl_;

};

#endif 

