/* 
 *  Anti SG:
        định lý SJ:
            điều kiện để người đầu tiên chiến thắng là 
                + giá trị SG của trò chơi hiện tại bằng 0 và tất cả 
                các trò chơi con có SG không vướt quá 1
                + giá trị SG khác 0 và có ít nhất một trò chơi con 
                có SG lớn hơn 1

        nếu bất kì pile nào có số viên sỏi lớn hơn 1 thì ta luôn 
        tồn tại một trạng thái của trò chơi con có SG > 1 

        vì vậy ta chỉ cần check giá trị của ai
        
        
        This number x can be found in the following recursive way:
Calculate the Sprague-Grundy value x_i for each transition (v, v_i), and then we 
can calculate
x as mex(x_1, … , x_k), where the mex function for a set of numbers returns the 
smallest non-negative number not present in that set
 */
