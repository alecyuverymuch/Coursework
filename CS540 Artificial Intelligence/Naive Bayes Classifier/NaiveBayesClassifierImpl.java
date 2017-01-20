/**
 * Your implementation of a naive bayes classifier. Please implement all four methods.
 */

public class NaiveBayesClassifierImpl implements NaiveBayesClassifier {
	
	private double countSPAM,countHAM,messageSize,sizeSPAM,sizeHAM;
	private Instance[] trainingData;
	
	/**
	 * Trains the classifier with the provided training data and vocabulary size
	 */
	@Override
	public void train(Instance[] trainingData, int v) {
		//initialize all the private instance data
		countSPAM = 0;
		countHAM = 0;
		sizeSPAM = 0;
		sizeHAM = 0;
		messageSize = v;
		this.trainingData = trainingData;
		//go through every instance in the training data
		for (Instance instance:trainingData)
		{
			//if the instance is SPAM increment the count and increment the size
			//by the size of the instance's words
			if (instance.label.equals(Label.SPAM))
			{
				countSPAM++;
				sizeSPAM+=instance.words.length;
			}
			//if HAM, do the same for the HAM variables
			else
			{
				countHAM++;
				sizeHAM+=instance.words.length;
			}
		}
	}

	/**
	 * Returns the prior probability of the label parameter, i.e. P(SPAM) or P(HAM)
	 */
	@Override
	public double p_l(Label label) {
		//if SPAM, return the count of SPAM instances divided by the total 
		//number of instances
		if (label.equals(Label.SPAM))
			return countSPAM/(double)trainingData.length;
		//if HAM, return the count divided by the total instances
		return countHAM/(double)trainingData.length;
	}

	/**
	 * Returns the smoothed conditional probability of the word given the label,
	 * i.e. P(word|SPAM) or P(word|HAM)
	 */
	@Override
	public double p_w_given_l(String word, Label label) {
		//initialize a count and a delta
		double tokenCount = 0;
		double delt = 0.00001;
		//go through every instance, if it has a matching label, count the 
		//number of tokens that are equal to the given word
		for(Instance instance : trainingData)
			if (instance.label.equals(label))
				for (String token : instance.words)
					if (token.equals(word))
						tokenCount++;
		//return the probability of the word occuring given the label using 
		//smoothing
		if (label.equals(Label.SPAM))
			return (tokenCount+delt)/(((double)messageSize*delt)+sizeSPAM);
		return (tokenCount+delt)/(((double)messageSize*delt)+sizeHAM);
	}
	
	/**
	 * Classifies an array of words as either SPAM or HAM. 
	 */
	@Override
	public ClassifyResult classify(String[] words) {
		//create a new classify result object
		ClassifyResult classify = new ClassifyResult();
		//calculate the log probability for each label
		double logProbSPAM = Math.log(p_l(Label.SPAM));
		double logProbHAM = Math.log(p_l(Label.HAM));
		for (String word : words)
		{
			logProbSPAM+=Math.log(p_w_given_l(word,Label.SPAM));
			logProbHAM+=Math.log(p_w_given_l(word,Label.HAM));
		}
		//set the label of the words to the label with the highest log 
		//probability
		if (logProbSPAM>logProbHAM)
			classify.label=Label.SPAM;
		else
			classify.label=Label.HAM;
		//set the log probabilities for the labels
		classify.log_prob_spam=logProbSPAM;
		classify.log_prob_ham=logProbHAM;
		//return the classify result object
		return classify;
	}
}
