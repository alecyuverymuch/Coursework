import java.util.ArrayList;
import java.util.List;
import java.util.Map;
import java.util.Stack;

/**
 * Fill in the implementation details of the class DecisionTree using this file.
 * Any methods or secondary classes that you want are fine but we will only
 * interact with those methods in the DecisionTree framework.
 * 
 * You must add code for the 5 methods specified below.
 * 
 * See DecisionTree for a description of default methods.
 */
public class DecisionTreeImpl extends DecisionTree {
	private DecTreeNode root;
	private List<String> labels; // ordered list of class labels
	private List<String> attributes; // ordered list of attributes
	private Map<String, List<String>> attributeValues; // map to ordered
														// discrete values taken
														// by attributes
	/**
	 * Answers static questions about decision trees.
	 */
	DecisionTreeImpl() {
		// no code necessary
		// this is void purposefully
	}

	/**
	 * Build a decision tree given only a training set.
	 * 
	 * @param train: the training set
	 */
	DecisionTreeImpl(DataSet train) {

		this.labels = train.labels;
		this.attributes = train.attributes;
		this.attributeValues = train.attributeValues;
		//get the root's default value
		int def = majorityVote(train.instances);
		//build the tree
		root = buildTree(train.instances, train.attributes, def, -1);
	}
	
	/**
	 * Build a decision tree given a training set then prune it using a tuning
	 * set.
	 * 
	 * @param train: the training set
	 * @param tune: the tuning set
	 */
	DecisionTreeImpl(DataSet train, DataSet tune) {

		this.labels = train.labels;
		this.attributes = train.attributes;
		this.attributeValues = train.attributeValues;
		//get the root's default value
		int def = majorityVote(train.instances);
		//build the tree
		root = buildTree(train.instances, train.attributes, def, -1);
		double accuracy = accuracy(tune.instances);
		//prune the tree
		prune(tune.instances,root,accuracy);
	}
	
	/**
	 * builds a decision tree based off 
	 * @param examples
	 * @param questions
	 * @param def
	 * @param parentAttr
	 * @return
	 */
	private DecTreeNode buildTree (List<Instance> examples, List<String> questions, int def, int parentAttr){
		//if there are no more examples, return a node with the parents label
		if (examples==null||examples.isEmpty())
			return new DecTreeNode(def,-1,parentAttr,true);
		//if there are no more questions, return a node with the majority label
		if (questions==null||questions.isEmpty())
			return new DecTreeNode(majorityVote(examples),-1,parentAttr,true);
        //if all the examples have the same label, return a node with the label
        if (sameLabel(examples)) {
            return new DecTreeNode(examples.get(0).label, -1, parentAttr, true);
        }
		String question = bestQuestion(examples,questions);
		int questionIndex = attributes.indexOf(question);
		//create a new list of questions and remove the current best question
		List<String> newQuestions=new ArrayList<String>();
        for (String currQuestion : questions) 
            newQuestions.add(currQuestion);
        newQuestions.remove(question);
        //create a new node
		DecTreeNode newNode = new DecTreeNode(majorityVote(examples), questionIndex, parentAttr, false);
		//get all the different possible answers to the question
		List<String> answers =attributeValues.get(question);
		//if there are no answers, return the new node
        if (answers==null) 
            return newNode;
        //go through all the answers
        for (int i = 0; i < answers.size(); i++)
        {
        	//create a new list of examples with the attribute values matching 
        	//that of the answer
        	List<Instance> newExamples = new ArrayList<Instance>();
        	for(Instance example : examples)
				if (example.attributes.get(questionIndex)==i)
					newExamples.add(example);
        	//add a child to the new node by calling buildTree recursively
            newNode.addChild(buildTree(newExamples, newQuestions,majorityVote(examples),i));
        }
		return newNode;
		
	}
	
	/**
	 * returns the best question based on the attribute with the highest gain
	 * @param examples
	 * @param questions
	 * @return the best question
	 */
	public String bestQuestion(List<Instance> examples, List<String> questions){
		//start at question 1 and get the gain
		int question = 0;
		double max = infoGain(examples,questions.get(question));
		//go through each gain value
		for (int i = 1; i < questions.size(); i++)
		{
			//if the gain is better, use it
			if (infoGain(examples,questions.get(i))>max)
			{
				question = i;
				max = infoGain(examples,questions.get(i));
			}
		}
		//return the question at the index of the best question
		return questions.get(question);
	}
	
	/**
	 * returns the entropy of the examples
	 * @param examples
	 * @return entropy
	 */
	public double entropy(List<Instance> examples){
		//double for the entropy
		double entropy = 0;
		//go through all the possible label values
		for (int i = 0; i < labels.size(); i++)
		{
			//count variable
			int count = 0;
			//go through all the examples, it the label is equal to the current
			//label, then increment the count
			for (int j = 0; j < examples.size(); j++)
			{
				if (examples.get(j).label==i)
				{
					count++;
				}
			}
			//probability is number of occurrences divided by number of examples
			double probability = (double)count/(double)examples.size();
			//if not empty and probability is > 0, then subtract Pr*log2(Pr) 
			//from entropy
			if (probability > 0)
			{
				entropy -= probability * (Math.log(probability)/Math.log(2));
			}
		}
		return entropy;
	}
	
	/**
	 * returns the conditional entropy given that an attribute occurs
	 * @param examples
	 * @param questions
	 * @param attribute
	 * @return conditional entropy
	 */
	public double conditionalEntropy(List<Instance> examples, String attribute){
		//the conditional entropy to be returned
		double conditionalEntropy = 0;
		//index of the attribute from the list of questions
		int questionIndex = attributes.indexOf(attribute);
		//A list of the different values that the attribute can have
		List<String> values = attributeValues.get(attribute);
		//loop through the different possible values of the attribute
		for (int x = 0; x < values.size(); x++)
		{
			//int for counting attributes
			int attrCount = 0; 
			//loop though examples, if the attribute at the given index is equal
			//to the current value, increment count
			for (int y = 0; y < examples.size(); y++)
				if (examples.get(y).attributes.get(questionIndex)==x)
					attrCount++;
			//the probability for the attribute to occur is the number of 
			//Occurrences divided by the total number of examples
			double attrProbability = (double)attrCount/(double)examples.size();
			//double for the entropy
			double entropy = 0;
			//go through all the possible label values
			for (int i = 0; i < labels.size(); i++)
			{
				//count variable
				int count = 0;
				//go through all the examples, it the label is equal to the 
				//current label and value of the example's attribute is equal to 
				//the current attribute, then increment the count
				for (int j = 0; j < examples.size(); j++)
					if (examples.get(j).label==i&&examples.get(j).attributes.get(questionIndex)==x)
						count++;
				//probability is number of times the examples has the desired 
				//label and desired attribute divided by the number of times it
				//just has the desired attribute
				double probability = ((double)count/(double)attrCount);
				//if not empty and probability is > 0, then subtract Pr*log2(Pr) 
				//from entropy
				if (examples.size()!=0 && probability > 0 && attrProbability > 0)
				{
					entropy -= probability * (Math.log(probability)/Math.log(2));
				}
			}
			//conditional entropy is the original entropy times the probability 
			//that the attribute occurs
			conditionalEntropy+=attrProbability*entropy;
		}
		return conditionalEntropy;
	}
	
	/**
	 * returns an array of the info gains from each attribute
	 * @param examples
	 * @param questions
	 * @return array of info gains
	 */
	public double infoGain(List<Instance> examples, String attribute){
		//an array to hold the gains of using different questions
		double gain = 0;
		//the entropy given by the examples 
		double entropy = entropy(examples);
		//gain is entropy - conditionalEntropy
		gain = entropy-conditionalEntropy(examples,attribute);
		return gain;
	}
		
	/**
	 * checks if all the given examples have the same label
	 * @param examples
	 * @return true if all labels are the same, false if not
	 */
	public boolean sameLabel(List<Instance> examples){
		//go through every example
        for (Instance example:examples) 
        {
        	//if the example's label is not the same as the others return false
            if (example.label.intValue()!=examples.get(0).label) 
            {
                return false;
            }
        }
        return true;
	}
	
	/**
	 * takes the majority vote of the labels from the list of examples
	 * @param examples
	 * @return the majority vote
	 */
	public int majorityVote(List<Instance> examples){
		//creates a array to hold the count of each label
		int [] vote = new int[labels.size()];
		//go through each example and tally up the number of times every label 
		//occurs
		for(int i = 0; i < examples.size(); i++)
		{
			vote[examples.get(i).label]++;
		}
		//start at the first label and get the count
		int majority = 0;
		int majorityCount = vote[0];
		for(int j = 1; j < vote.length; j++)
		{
			//if the current count is greater than the old one, use it as the 
			//max
			if (vote[j]>majorityCount)
			{
				majority = j;
				majorityCount = vote[j];
			}
				
		}
		return majority;
	}
	/**
	 * prunes the tree using the tuning data 
	 * DOES NOT WORK
	 * @param tuneData
	 * @param node
	 * @param pAccuracy
	 */
	public void prune(List<Instance> tuneData, DecTreeNode node, double pAccuracy){
		//the max accuracy is zero and the index is -1
		double maxAcc = 0;
		int max = -1;
		//if there are no children, the node is terminal and return
		if (node.children==null||node.children.isEmpty())
		{
			node.terminal=true;
			return;
		}
		//create a copy of the tree
		DecTreeNode tree = new DecTreeNode(node.label,node.attribute,node.parentAttributeValue,node.terminal);
		for (DecTreeNode child : node.children)
			tree.children.add(child);
		//for every child that the tree has 
		for (DecTreeNode child : tree.children)
		{
			//get the index and remove the child from node
			int childIndex = node.children.indexOf(child);
			node.children.remove(childIndex);
			//get the accuracy of the tree without the node
        	double accuracy = accuracy(tuneData);
        	//if the accuracy is greater than the max accuracy, keep the index 
        	//and accuracy value
        	if (accuracy > maxAcc)
        	{
        		max = childIndex;
        		maxAcc = accuracy;
        	}
        	//add the child back 
        	node.children.add(childIndex,child);
        	
		}
		//if the max accuracy is greater than the parent attribute
		if (maxAcc>pAccuracy)
		{
			//remove the child so that it will yeild the highest accuracy
			node.children.remove(max);
			//get the node's children and prune them
			for (DecTreeNode child : node.children)
			{
				prune(tuneData, child, maxAcc);
			}
		}
	}
	
	/**
	 * gets the accuracy of the decision tree buy using the tune data
	 * @param tuneData
	 * @return the accuracy of the tree
	 */
	public double accuracy(List<Instance> tuneData){
		//an int for counting number of correct identifications
		int count = 0; 
		//go through every instance 
		for (Instance data : tuneData)
			//if the classification is correct, increment count
			if (classify(data).equals(data.label))
				count++;
		//return the accuracy as the count divided by the size of the data. 
		return (double)count/(double)tuneData.size();
	}
	
	@Override
	public String classify(Instance instance) {
		//start at the root node
		DecTreeNode currNode=root;
        //keep going down the tree until you reach a terminal node
        while (!currNode.terminal) 
        {
            //get the size of the current node's children
            int childrenSize = currNode.children.size();
            //go through every child
            for (int i = 0; i < childrenSize; i++) 
            {
            	//get the current child
            	DecTreeNode child = currNode.children.get(i);
            	//if the parent's attribute value is the same as the attributes
            	//set the current node equal to the child
                if (child.parentAttributeValue==instance.attributes.get(currNode.attribute)) 
                {
                    currNode=child;
                    i = childrenSize;
                }
            } 	
        }
        return labels.get(currNode.label);
	}

	@Override
	/**
	 * Print the decision tree in the specified format
	 */
	public void print() {

		printTreeNode(root, null, 0);
	}
	
	/**
	 * Prints the subtree of the node
	 * with each line prefixed by 4 * k spaces.
	 */
	public void printTreeNode(DecTreeNode p, DecTreeNode parent, int k) {
		StringBuilder sb = new StringBuilder();
		for (int i = 0; i < k; i++) {
			sb.append("    ");
		}
		String value;
		if (parent == null) {
			value = "ROOT";
		} else{
			String parentAttribute = attributes.get(parent.attribute);
			value = attributeValues.get(parentAttribute).get(p.parentAttributeValue);
		}
		sb.append(value);
		if (p.terminal) {
			sb.append(" (" + labels.get(p.label) + ")");
			System.out.println(sb.toString());
		} else {
			sb.append(" {" + attributes.get(p.attribute) + "?}");
			System.out.println(sb.toString());
			for(DecTreeNode child: p.children) {
				printTreeNode(child, p, k+1);
			}
		}
	}

	@Override
	public void rootInfoGain(DataSet train) {

		
		this.labels = train.labels;
		this.attributes = train.attributes;
		this.attributeValues = train.attributeValues;
		//go through each attribute and print the name and gain
		for (int i = 0; i < attributes.size(); i++)
		{
			double gain = infoGain(train.instances,attributes.get(i));
			System.out.format(attributes.get(i)+ " %.5f", gain);
			System.out.println();
		}
	}
	

}
