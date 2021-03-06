
#include "simriscv.h"

#include "def.h"
#define V 0
std::stringstream lastCmd;

SimRISCV::SimRISCV(){
	pc = 0x80000000;
	for(uint8_t i = 0;i<32;i++){
		gpregs[i]=0;
	}
	write_en = 0;
	read_en = 0;
	byte_en = 0;
	write_data = 0;
	addr = 0;

}
SimRISCV * SimRISCV::get_sim(){

	static SimRISCV instance;
	instance.gpregs[0] = 0;
	return &instance;
}

void SimRISCV::reset(){
	SimRISCV* tmp = get_sim();
	tmp->pc =  0x80000000;
	std::cout << tmp->pc<<std::endl;
	for(uint8_t i = 0;i<32;i++){
		tmp->gpregs[i]=0;
	}
	tmp->write_en = 0;
	tmp->read_en = 0;
	tmp->byte_en = 0;
	tmp->write_data = 0;
	tmp->addr = 0;
}
void SimRISCV::ori(int rd,int rs1,int imm){
	SimRISCV* tmp = get_sim();
	tmp->pc += 4;
	tmp->gpregs[rd] = imm | tmp->gpregs[rs1];
	lastCmd.str("");
	lastCmd << "ori "<< rd <<","<<rs1<<","<< imm;
	if (V) std::cout << lastCmd.str() << std::endl;


}
void SimRISCV::andi(int rd,int rs1,int imm){
	SimRISCV* tmp = get_sim();
	tmp->pc += 4;
	tmp->gpregs[rd] = imm & tmp->gpregs[rs1];
	lastCmd.str("");
	lastCmd << "andi "<< rd <<","<<rs1<<","<< imm;
	if (V) std::cout << lastCmd.str() << std::endl;

}
void SimRISCV::addi(int rd,int rs1,int imm){
	lastCmd.str("");
	lastCmd << "addi "<< rd <<","<<rs1<<","<< imm;
	if (V) std::cout << lastCmd.str() << std::endl;
	SimRISCV* tmp = get_sim();
	tmp->pc += 4;
	tmp->gpregs[rd] = imm + tmp->gpregs[rs1];
	

}
void SimRISCV::xori(int rd,int rs1,int imm){
	lastCmd.str("");
	lastCmd << "xori "<< rd <<","<<rs1<<","<< imm;
	if (V) std::cout << lastCmd.str() << std::endl;
	SimRISCV* tmp = get_sim();
	tmp->pc += 4;
	tmp->gpregs[rd] = imm ^ tmp->gpregs[rs1];
	

}
void SimRISCV::slti(int rd,int rs1,int imm){
	lastCmd.str("");
	lastCmd << "slti "<< rd <<","<<rs1<<","<< imm;
	if (V) std::cout << lastCmd.str() << std::endl;
	SimRISCV* tmp = get_sim();
	tmp->pc += 4;
	if(tmp->gpregs[rs1]<imm)
		tmp->gpregs[rd] = 1;
	else
		tmp->gpregs[rd] = 0;
	

}
void SimRISCV::sltiu(int rd,int rs1,int imm){
	lastCmd.str("");
	lastCmd << "sltiu "<< rd <<","<<rs1<<","<< imm;
	if (V) std::cout << lastCmd.str() << std::endl;
	SimRISCV* tmp = get_sim();
	tmp->pc += 4;
	if((uint32_t)tmp->gpregs[rs1]<(uint32_t)imm)
		tmp->gpregs[rd] = 1;
	else
		tmp->gpregs[rd] = 0;
	

}
void SimRISCV::slli(int rd,int rs1,int shamt){
	lastCmd.str("");
	lastCmd << "slli "<< rd <<","<<rs1<<","<< shamt;
	if (V) std::cout << lastCmd.str() << std::endl;
	SimRISCV* tmp = get_sim();
	tmp->pc += 4;
	tmp->gpregs[rd] = tmp->gpregs[rs1]<<shamt;
	

}
void SimRISCV::srli(int rd,int rs1,int shamt){
	lastCmd.str("");
	lastCmd << "srli "<< rd <<","<<rs1<<","<< shamt;
	if (V) std::cout << lastCmd.str() << std::endl;
	SimRISCV* tmp = get_sim();
	tmp->pc += 4;
	tmp->gpregs[rd] = (uint32_t)tmp->gpregs[rs1]>>shamt;
	

}
void SimRISCV::sll(int rd,int rs1,int rs2){
	lastCmd.str("");
	lastCmd << "sll "<< rd <<","<<rs1<<","<< rs2;
	if (V) std::cout << lastCmd.str() << std::endl;
	SimRISCV* tmp = get_sim();
	tmp->pc += 4;
	if((uint32_t)tmp->gpregs[rs2]>=32)
	tmp->gpregs[rd] = 0;
	else
	tmp->gpregs[rd] = ((uint32_t)tmp->gpregs[rs1])<<((uint32_t)tmp->gpregs[rs2]);


}
void SimRISCV::srl(int rd,int rs1,int rs2){
	lastCmd.str("");
	lastCmd << "srl "<< rd <<","<<rs1<<","<< L2 rs2;
	if (V) std::cout << lastCmd.str() << std::endl;
	SimRISCV* tmp = get_sim();
	tmp->pc += 4;
	if((uint32_t)tmp->gpregs[rs2]>=32)
	tmp->gpregs[rd] = 0;
	else
	tmp->gpregs[rd] = ((uint32_t)tmp->gpregs[rs1])>>((uint32_t)tmp->gpregs[rs2]);


}
void SimRISCV::andr(int rd,int rs1,int rs2){
	lastCmd.str("");
	lastCmd << "and "<< rd <<","<<rs1<<","<< L2 rs2;
	if (V) std::cout << lastCmd.str() << std::endl;
	SimRISCV* tmp = get_sim();
	tmp->pc += 4;
	tmp->gpregs[rd] = (tmp->gpregs[rs1])&(tmp->gpregs[rs2]);


}
void SimRISCV::orr(int rd,int rs1,int rs2){
	lastCmd.str("");
	lastCmd << "or "<< rd <<","<<rs1<<","<< L2 rs2;
	if (V) std::cout << lastCmd.str() << std::endl;
	SimRISCV* tmp = get_sim();
	tmp->pc += 4;
	tmp->gpregs[rd] = (tmp->gpregs[rs1])|(tmp->gpregs[rs2]);


}
void SimRISCV::xorr(int rd,int rs1,int rs2){
	lastCmd.str("");
	lastCmd << "xor "<< rd <<","<<rs1<<","<< L2 rs2;
	if (V) std::cout << lastCmd.str() << std::endl;
	SimRISCV* tmp = get_sim();
	tmp->pc += 4;
	tmp->gpregs[rd] = (tmp->gpregs[rs1])^(tmp->gpregs[rs2]);


}
void SimRISCV::slt(int rd,int rs1,int rs2){
	lastCmd.str("");
	lastCmd << "slt "<< rd <<","<<rs1<<","<< L2 rs2;
	if (V) std::cout << lastCmd.str() << std::endl;
	SimRISCV* tmp = get_sim();
	tmp->pc += 4;
	if((tmp->gpregs[rs1])<(tmp->gpregs[rs2]))
	tmp->gpregs[rd] = 1;
	else
	tmp->gpregs[rd] = 0;

}
void SimRISCV::sltu(int rd,int rs1,int rs2){
	lastCmd.str("");
	lastCmd << "sltu "<< rd <<","<<rs1<<","<< L2 rs2;
	if (V) std::cout << lastCmd.str() << std::endl;
	SimRISCV* tmp = get_sim();
	tmp->pc += 4;
	if(((uint32_t)tmp->gpregs[rs1])<((uint32_t)tmp->gpregs[rs2]))
	tmp->gpregs[rd] = 1;
	else
	tmp->gpregs[rd] = 0;

}
void SimRISCV::sra(int rd,int rs1,int rs2){
	lastCmd.str("");
	lastCmd << "sra "<< rd <<","<<rs1<<","<< L2 rs2;
	if (V) std::cout << lastCmd.str() << std::endl;
	SimRISCV* tmp = get_sim();
	tmp->pc += 4;
	if((uint32_t)tmp->gpregs[rs2]>=32)
	tmp->gpregs[rd] =  (tmp->gpregs[rs1])>>(31);
	else
	tmp->gpregs[rd] = (tmp->gpregs[rs1])>>((uint32_t)tmp->gpregs[rs2]);


}
void SimRISCV::srai(int rd,int rs1,int shamt){
	lastCmd.str("");
	lastCmd << "srai "<< rd <<","<<rs1<<","<< shamt;
	if (V) std::cout << lastCmd.str() << std::endl;
	SimRISCV* tmp = get_sim();
	tmp->pc += 4;
	tmp->gpregs[rd] = tmp->gpregs[rs1]>>shamt;
	

}
void SimRISCV::add(int rd,int rs1,int rs2){
	lastCmd.str("");
	lastCmd << "add "<< L2 rd <<","<<rs1<<","<< rs2;
	if (V) std::cout << lastCmd.str() << std::endl;
	SimRISCV* tmp = get_sim();
	tmp->pc += 4;
	tmp->gpregs[rd] = tmp->gpregs[rs1]+tmp->gpregs[rs2];
	

}
void SimRISCV::sub(int rd,int rs1,int rs2){
	lastCmd.str("");
	lastCmd << "sub "<< L2 rd <<","<<rs1<<","<< rs2;
	if (V) std::cout << lastCmd.str() << std::endl;
	SimRISCV* tmp = get_sim();
	tmp->pc += 4;
	tmp->gpregs[rd] = tmp->gpregs[rs1]-tmp->gpregs[rs2];
	

}
void SimRISCV::lui(int rd,int imm){
	lastCmd.str("");
	lastCmd << "lui "<< rd <<","<< HEX imm;
	if (V) std::cout << lastCmd.str() << std::endl;
	SimRISCV* tmp = get_sim();
	tmp->pc += 4;
	tmp->gpregs[rd] = imm<<12;
	

}
void SimRISCV::auipc(int rd,int imm){
	lastCmd.str("");
	lastCmd << "auipc "<< rd <<","<< HEX imm;
	if (V) std::cout << lastCmd.str() << std::endl;
	SimRISCV* tmp = get_sim();
	tmp->gpregs[rd] = tmp->pc +  (imm<<12);
	tmp->pc += 4;
	
	

}
void SimRISCV::jal(int rd,int imm){
	lastCmd.str("");
	lastCmd << "jal "<< rd <<","<< HEX imm;
	if (V) std::cout << lastCmd.str() << std::endl;
	SimRISCV* tmp = get_sim();
	tmp->gpregs[rd] = tmp->pc + 4;
	tmp->pc += imm<<1;
	
	

}
void SimRISCV::jalr(int rd,int rs,int imm){
	lastCmd.str("");
	lastCmd << "jalr "<< rd <<","<< rs <<","<< HEX imm;
	if (V) std::cout << lastCmd.str() << std::endl;
	SimRISCV* tmp = get_sim();
	uint32_t pc_tmp = tmp->pc;
	tmp->pc = (imm + tmp->gpregs[rs]) & 0xFFFFFFFE;
	tmp->gpregs[rd] = pc_tmp + 4;
}
void SimRISCV::beq(int rs1,int rs2,int imm){
	lastCmd.str("");
	lastCmd << "beq "<< rs1 <<","<< rs2 <<","<< HEX imm;
	if (V) std::cout << lastCmd.str() << std::endl;
	SimRISCV* tmp = get_sim();
	uint32_t pc_tmp = tmp->pc;
	if(tmp->gpregs[rs1] == tmp->gpregs[rs2]){
		tmp->pc += imm<<1;
	}
	else
		tmp->pc += 4;
}
void SimRISCV::bne(int rs1,int rs2,int imm){
	lastCmd.str("");
	lastCmd << "bne "<< rs1 <<","<< rs2 <<","<< HEX imm;
	if (V) std::cout << lastCmd.str() << std::endl;
	SimRISCV* tmp = get_sim();
	uint32_t pc_tmp = tmp->pc;
	if(tmp->gpregs[rs1] != tmp->gpregs[rs2]){
		tmp->pc += imm<<1;
	}
	else
		tmp->pc += 4;
}
void SimRISCV::blt(int rs1,int rs2,int imm){
	lastCmd.str("");
	lastCmd << "blt "<< rs1 <<","<< rs2 <<","<< HEX imm;
	if (V) std::cout << lastCmd.str() << std::endl;
	SimRISCV* tmp = get_sim();
	uint32_t pc_tmp = tmp->pc;
	if(tmp->gpregs[rs1] < tmp->gpregs[rs2]){
		tmp->pc += imm<<1;
	}
	else
		tmp->pc += 4;
}
void SimRISCV::bltu(int rs1,int rs2,int imm){
	lastCmd.str("");
	lastCmd << "bltu "<< rs1 <<","<< rs2 <<","<< HEX imm;
	if (V) std::cout << lastCmd.str() << std::endl;
	SimRISCV* tmp = get_sim();
	uint32_t pc_tmp = tmp->pc;
	if((uint32_t)tmp->gpregs[rs1] < (uint32_t)tmp->gpregs[rs2]){
		tmp->pc += imm<<1;
	}
	else
		tmp->pc += 4;
}
void SimRISCV::bge(int rs1,int rs2,int imm){
	lastCmd.str("");
	lastCmd << "bge "<< rs1 <<","<< rs2 <<","<< HEX imm;
	if (V) std::cout << lastCmd.str() << std::endl;
	SimRISCV* tmp = get_sim();
	uint32_t pc_tmp = tmp->pc;
	if(tmp->gpregs[rs1] >= tmp->gpregs[rs2]){
		tmp->pc += imm<<1;
	}
	else
		tmp->pc += 4;
}
void SimRISCV::bgeu(int rs1,int rs2,int imm){
	lastCmd.str("");
	lastCmd << "bgeu "<< rs1 <<","<< rs2 <<","<< HEX imm;
	if (V) std::cout << lastCmd.str() << std::endl;
	SimRISCV* tmp = get_sim();
	uint32_t pc_tmp = tmp->pc;
	if((uint32_t)tmp->gpregs[rs1] >= (uint32_t)tmp->gpregs[rs2]){
		tmp->pc += imm<<1;
	}
	else
		tmp->pc += 4;
}
void SimRISCV::sw(int rs1,int rs2,int imm){
	lastCmd.str("");
	lastCmd << "sw "<< rs1 <<","<< rs2 <<","<< HEX imm;
	if (V) std::cout << lastCmd.str() << std::endl;
	SimRISCV* tmp = get_sim();
	tmp->pc += 4;
	tmp->write_en = 1;
	tmp->byte_en = 0xF;
	tmp->write_data = tmp->gpregs[rs2];
	tmp->addr =  tmp->gpregs[rs1] + imm;

}
void SimRISCV::sh(int rs1,int rs2,int imm){
	lastCmd.str("");
	lastCmd << "sh "<< rs1 <<","<< rs2 <<","<< HEX imm;
	if (V) std::cout << lastCmd.str() << std::endl;
	SimRISCV* tmp = get_sim();
	tmp->pc += 4;
	tmp->write_en = 1;
	tmp->byte_en = 0x3;
	tmp->write_data = tmp->gpregs[rs2];
	tmp->addr =  tmp->gpregs[rs1] + imm;

}
void SimRISCV::sb(int rs1,int rs2,int imm){
	lastCmd.str("");
	lastCmd << "sb "<< rs1 <<","<< rs2 <<","<< HEX imm;
	if (V) std::cout << lastCmd.str() << std::endl;
	SimRISCV* tmp = get_sim();
	tmp->pc += 4;
	tmp->write_en = 1;
	tmp->byte_en = 0x1;
	tmp->write_data = tmp->gpregs[rs2];
	tmp->addr =  tmp->gpregs[rs1] + imm;

}
void SimRISCV::lb(int rd,int rs1,int imm,int data){
	lastCmd.str("");
	lastCmd << "lb "<< rd <<","<< rs1 <<","<< HEX imm <<":=" << HEX data;
	if (V) std::cout << lastCmd.str() << std::endl;
	SimRISCV* tmp = get_sim();
	tmp->pc += 4;
	tmp->read_en = 1;
	tmp->byte_en = 0x1;
	tmp->addr =  tmp->gpregs[rs1] + imm;
	if(data&0x80)
		tmp->gpregs[rd] = 0xFFFFFF00|(data&0xFF);
	else
		tmp->gpregs[rd] = (data&0xFF);

}
void SimRISCV::lbu(int rd,int rs1,int imm,int data){
	lastCmd.str("");
	lastCmd << "lbu "<< rd <<","<< rs1 <<","<< HEX imm <<":=" << HEX data;
	if (V) std::cout << lastCmd.str() << std::endl;
	SimRISCV* tmp = get_sim();
	tmp->pc += 4;
	tmp->read_en = 1;
	tmp->byte_en = 0x1;
	tmp->addr =  tmp->gpregs[rs1] + imm;
	tmp->gpregs[rd] = (data&0xFF);

}
void SimRISCV::lh(int rd,int rs1,int imm,int data){
	lastCmd.str("");
	lastCmd << "lh "<< rd <<","<< rs1 <<","<< HEX imm <<":=" << HEX data;
	if (V) std::cout << lastCmd.str() << std::endl;
	SimRISCV* tmp = get_sim();
	tmp->pc += 4;
	tmp->read_en = 1;
	tmp->byte_en = 0x3;
	tmp->addr =  tmp->gpregs[rs1] + imm;
	if(data&0x8000)
		tmp->gpregs[rd] = 0xFFFF0000|(data&0xFFFF);
	else
		tmp->gpregs[rd] = (data&0xFFFF);

}
void SimRISCV::lhu(int rd,int rs1,int imm,int data){
	lastCmd.str("");
	lastCmd << "lhu "<< rd <<","<< rs1 <<","<< HEX imm <<":=" << HEX data;
	if (V) std::cout << lastCmd.str() << std::endl;
	SimRISCV* tmp = get_sim();
	tmp->pc += 4;
	tmp->read_en = 1;
	tmp->byte_en = 0x3;
	tmp->addr =  tmp->gpregs[rs1] + imm;
	tmp->gpregs[rd] = (data&0xFFFF);

}
void SimRISCV::lw(int rd,int rs1,int imm,int data){
	lastCmd.str("");
	lastCmd << "lw "<< rd <<","<< rs1 <<","<< HEX imm <<":=" << HEX data;
	if (V) std::cout << lastCmd.str() << std::endl;
	SimRISCV* tmp = get_sim();
	tmp->pc += 4;
	tmp->read_en = 1;
	tmp->byte_en = 0xF;
	tmp->addr =  tmp->gpregs[rs1] + imm;
	tmp->gpregs[rd] = data;

}
//return error string
uint32_t SimRISCV::score(cpu* uut,std::stringstream& emesg){
	SimRISCV* tmp = get_sim();
	uint32_t errors = 0;
	emesg << "Last Cmd => " << lastCmd.str() << std::endl;
	emesg << HEX (int)uut->PC<< std::endl;
	if(uut->PC!=tmp->pc){
		//emesg << "Bad PC" << "\n";
		emesg << "Pc = " << HEX (int)uut->PC << " expected = " << HEX tmp->pc << std::endl;
		errors++;
	}
	for(int i = 0;i<32;i++){
		if(uut->cpu_top__DOT__GPREGS[i]!=tmp->gpregs[i]){
			//emesg.append("Bad reg");
			emesg << "GPREG["<< L2 i <<"] = ";
			emesg << HEX (int)uut->cpu_top__DOT__GPREGS[i] << " expected = "<< HEX tmp->gpregs[i] << std::endl;
			errors++;
		}
	}
	if(uut->write_en!=tmp->write_en){
		emesg << "write_en = " << HEX (int)uut->write_en << " write_en = " << HEX tmp->write_en << std::endl;
		errors++;
	}
	if(uut->read_en!=tmp->read_en){
		emesg << "read_en = " << HEX (int)uut->read_en << " read_en = " << HEX tmp->read_en << std::endl;
		errors++;
	}
	if(uut->byte_en!=tmp->byte_en){
		emesg << "byte_en = " << HEX (int)uut->byte_en << " byte_en = " << HEX tmp->byte_en << std::endl;
		errors++;
	}
	if(uut->write_data!=tmp->write_data){
		emesg << "write_data = " << HEX (int)uut->write_data << " write_data = " << HEX tmp->write_data << std::endl;
		errors++;
	}
	
	if(uut->addr!=tmp->addr){
		emesg << "addr = " << HEX (int)uut->addr << " addr = " << HEX tmp->addr << std::endl;
		errors++;
	}


	tmp->write_en = 0;
	tmp->read_en = 0;
	tmp->byte_en = 0;
	tmp->write_data = 0;
	tmp->addr = 0;

	return errors;
}