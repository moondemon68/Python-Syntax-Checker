def get_rule_category(rule: dict) -> str:
    ''' Get rule category in string. This category is also a key for its corresponding dictionary.
        Input(dict) = rule
        Output(str) = category of the rule
 
        Example:
        Input   = {'producer': 'N', 'product': ['people']}
        Output  = 'terminal'
    '''
    rule_product = rule[PRODUCT_KEY]
    if len(rule_product) == 0:
        return EPSILON_RULE_KEY
    elif len(rule_product) == 1:    # here
        if rule_product[0].islower:
            return TERMINAL_RULE_KEY
        else:
            return UNARY_RULE_KEY
    elif len(rule_product) == 2:
        return BINARY_RULE_KEY
    else:
        return N_ARIES_RULE_KEY
'''
def variable openparentheses variable colon variable closeparentheses colon newline newline newline newline newline newline newline newline newline variable equal variable constant newline if variable openparentheses variable closeparentheses logicalop constant colon newline return variable newline elif variable openparentheses variable closeparentheses logicalop constant colon variable newline if variable constant logicalop variable colon newline return variable newline variable colon newline return variable newline elif variable openparentheses variable closeparentheses logicalop constant colon newline return variable newline variable colon newline return variable newline newline newline newline
'''